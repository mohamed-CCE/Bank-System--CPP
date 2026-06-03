#include <iostream>
#include <string>
using namespace std;
class Customer {
public:
    int accountNumber;
    string name;
    string phone;
    double balance;
    Customer* next;

    Customer(int acc, string n, string p, double b) {
        accountNumber = acc;
        name = n;
        phone = p;
        balance = b;
        next = NULL;
    }
};


class Transaction {
public:
    string type;
    int accountNumber;
    double amount;
    Transaction* next;

    Transaction(string t, int acc, double amt) {
        type = t;
        accountNumber = acc;
        amount = amt;
        next = NULL;
    }
};

class TransactionStack {
private:
    Transaction* top;

public:
    TransactionStack() {
        top = NULL;
    }

    void push(string type, int acc, double amt) {
        Transaction* newTransaction = new Transaction(type, acc, amt);
        newTransaction->next = top;
        top = newTransaction;
    }

    void display() {
        if (top == NULL) {
            cout << "\nNo transactions found.\n";
            return;
        }

        Transaction* temp = top;
        cout << "\n===== Transaction History =====\n";
        while (temp != NULL) {
            cout << "Type: " << temp->type
                << " | Account: " << temp->accountNumber
                << " | Amount: " << temp->amount << endl;
            temp = temp->next;
        }
    }
};


class CustomerQueue {
private:
    static const int SIZE = 10;
    string queue[SIZE];
    int front, rear;

public:
    CustomerQueue() {
        front = rear = -1;
    }

    bool isFull() {
        return (rear + 1) % SIZE == front;
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(string name) {
        if (isFull()) {
            cout << "Queue is full!\n";
            return;
        }

        if (isEmpty()) {
            front = rear = 0;
        }
        else {
            rear = (rear + 1) % SIZE;
        }

        queue[rear] = name;
        cout << name << " added to waiting queue.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }

        cout << queue[front] << " has been served.\n";

        if (front == rear) {
            front = rear = -1;
        }
        else {
            front = (front + 1) % SIZE;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }

        cout << "\n===== Customer Queue =====\n";
        int i = front;
        while (true) {
            cout << queue[i] << endl;
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
    }
};

class BankSystem {
private:
    Customer* head;
    TransactionStack transactions;
    CustomerQueue waitingQueue;

public:
    BankSystem() {
        head = NULL;
    }

    Customer* findCustomer(int acc) {
        Customer* temp = head;
        while (temp != NULL) {
            if (temp->accountNumber == acc)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }

    void createAccount() {
        int acc;
        string name, phone;
        double balance;

        cout << "Enter Account Number: ";
        cin >> acc;
        cin.ignore();

        if (findCustomer(acc) != NULL) {
            cout << "Account already exists!\n";
            return;
        }

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Phone: ";
        getline(cin, phone);

        cout << "Enter Initial Balance: ";
        cin >> balance;

        Customer* newCustomer = new Customer(acc, name, phone, balance);

        if (head == NULL) {
            head = newCustomer;
        }
        else {
            Customer* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newCustomer;
        }

        cout << "Account created successfully.\n";
    }

    void displayAccounts() {
        if (head == NULL) {
            cout << "No accounts found.\n";
            return;
        }

        Customer* temp = head;
        cout << "\n===== Customer Accounts =====\n";
        while (temp != NULL) {
            cout << "Account: " << temp->accountNumber
                << " | Name: " << temp->name
                << " | Phone: " << temp->phone
                << " | Balance: " << temp->balance << endl;
            temp = temp->next;
        }
    }

    void deposit() {
        int acc;
        double amount;
        cout << "Enter Account Number: ";
        cin >> acc;

        Customer* customer = findCustomer(acc);
        if (customer == NULL) {
            cout << "Account not found!\n";
            return;
        }

        cout << "Enter Amount: ";
        cin >> amount;

        customer->balance += amount;
        transactions.push("Deposit", acc, amount);

        cout << "Deposit successful.\n";
    }

    void withdraw() {
        int acc;
        double amount;
        cout << "Enter Account Number: ";
        cin >> acc;

        Customer* customer = findCustomer(acc);
        if (customer == NULL) {
            cout << "Account not found!\n";
            return;
        }

        cout << "Enter Amount: ";
        cin >> amount;

        if (amount > customer->balance) {
            cout << "Insufficient balance!\n";
            return;
        }

        customer->balance -= amount;
        transactions.push("Withdraw", acc, amount);

        cout << "Withdrawal successful.\n";
    }

    void transfer() {
        int fromAcc, toAcc;
        double amount;

        cout << "Enter Sender Account: ";
        cin >> fromAcc;
        cout << "Enter Receiver Account: ";
        cin >> toAcc;

        Customer* sender = findCustomer(fromAcc);
        Customer* receiver = findCustomer(toAcc);

        if (sender == NULL || receiver == NULL) {
            cout << "Invalid account(s)!\n";
            return;
        }

        cout << "Enter Amount: ";
        cin >> amount;

        if (amount > sender->balance) {
            cout << "Insufficient balance!\n";
            return;
        }

        sender->balance -= amount;
        receiver->balance += amount;

        transactions.push("Transfer", fromAcc, amount);

        cout << "Transfer successful.\n";
    }

    void searchAccount() {
        int acc;
        cout << "Enter Account Number: ";
        cin >> acc;

        Customer* customer = findCustomer(acc);

        if (customer == NULL) {
            cout << "Account not found!\n";
            return;
        }

        cout << "\nAccount Found:\n";
        cout << "Account: " << customer->accountNumber
            << " | Name: " << customer->name
            << " | Phone: " << customer->phone
            << " | Balance: " << customer->balance << endl;
    }

    void sortAccounts() {
        if (head == NULL || head->next == NULL) {
            cout << "Not enough accounts to sort.\n";
            return;
        }

        for (Customer* i = head; i != NULL; i = i->next) {
            for (Customer* j = i->next; j != NULL; j = j->next) {
                if (i->balance > j->balance) {
                    swap(i->accountNumber, j->accountNumber);
                    swap(i->name, j->name);
                    swap(i->phone, j->phone);
                    swap(i->balance, j->balance);
                }
            }
        }

        cout << "Accounts sorted by balance.\n";
    }

    void queueMenu() {
        int choice;
        string name;

        do {
            cout << "\n===== Customer Queue Menu =====\n";
            cout << "1. Add Customer to Queue\n";
            cout << "2. Serve Customer\n";
            cout << "3. Display Queue\n";
            cout << "4. Back\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                cout << "Enter Customer Name: ";
                getline(cin, name);
                waitingQueue.enqueue(name);
                break;
            case 2:
                waitingQueue.dequeue();
                break;
            case 3:
                waitingQueue.display();
                break;
            }
        } while (choice != 4);
    }

    void menu() {
        int choice;

        do {
            cout << "\n========== BANK SYSTEM ==========\n";
            cout << "1. Create Account\n";
            cout << "2. Display All Accounts\n";
            cout << "3. Deposit\n";
            cout << "4. Withdraw\n";
            cout << "5. Transfer\n";
            cout << "6. Search Account\n";
            cout << "7. Sort Accounts\n";
            cout << "8. Transaction History\n";
            cout << "9. Customer Queue\n";
            cout << "10. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1: createAccount(); break;
            case 2: displayAccounts(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: transfer(); break;
            case 6: searchAccount(); break;
            case 7: sortAccounts(); break;
            case 8: transactions.display(); break;
            case 9: queueMenu(); break;
            case 10: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
            }

        } while (choice != 10);
    }
};

int main() {
    BankSystem bank;
    bank.menu();
    return 0;
}
