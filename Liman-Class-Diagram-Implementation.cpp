#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Product {
public:
    int id;
    string name;
    float price;
    Product(int i, string n, float p) : id(i), name(n), price(p) {}
};

class ShoppingCart {
private:
    vector<pair<Product, int>> cart;
public:
    void addItem(Product product) {
        for (auto &item : cart) {
            if (item.first.id == product.id) {
                item.second++;
                cout << "Product added successfully!\n";
                return;
            }
        }
        cart.push_back({product, 1});
        cout << "Product added successfully!\n";
    }

    void viewCart() {
        if (cart.empty()) {
            cout << "Shopping cart is empty.\n";
            return;
        }
    
        float total = calculateTotal(); 
    
        cout << "\nShopping Cart:\n";
        cout << "---------------------------------------------\n";
        cout << "Total: " << fixed << setprecision(2) << total << endl; 
        cout << "---------------------------------------------\n";
        cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(10) << "Price" << "Quantity\n";
        cout << "---------------------------------------------\n";
        
        for (auto &item : cart) {
            cout << left << setw(10) << item.first.id << setw(15) << item.first.name
                 << setw(10) << item.first.price << item.second << endl;
        }
    }
    
    

    float calculateTotal() {
        float total = 0;
        for (auto &item : cart) total += item.first.price * item.second;
        return total;
    }

    vector<pair<Product, int>> getItems() { return cart; }
    void clear() { cart.clear(); }
};

class Order {
public:
    int orderId;
    float totalAmount;
    vector<pair<Product, int>> items;

    Order(int id, ShoppingCart cart) : orderId(id), totalAmount(cart.calculateTotal()), items(cart.getItems()) {}

    void display() {
        cout << "\nOrder ID: " << orderId << "\nTotal Amount: $" << totalAmount << "\n";
        cout << "---------------------------------------------\n";
        cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(10) << "Price" << "Quantity\n";
        cout << "---------------------------------------------\n";
        for (auto &item : items) {
            cout << left << setw(10) << item.first.id << setw(15) << item.first.name
                 << setw(10) << item.first.price << item.second << endl;
        }
    }
};

vector<Product> products = {
    {1, "Pencil", 5.00}, {2, "Notebook", 20.00}, {3, "Eraser", 3.00}, {4, "Pen", 10.00}
};

vector<Order> orders;

void viewProducts() {
    cout << "\nAvailable Products:\n";
    cout << "------------------------------------\n";
    cout << left << setw(10) << "ID" << setw(15) << "Name" << "Price\n";
    cout << "------------------------------------\n";
    for (auto &p : products) cout << left << setw(10) << p.id << setw(15) << p.name << p.price << endl;
}

void getValidInt(int &value) {
    while (!(cin >> value)) {
        cout << "Enter (1-4): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

char getValidYN() {
    char choice;
    while (true) {
        cin >> choice;
        if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n') {
            return choice;
        }
        cout << "Enter Y or N: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

int main() {
    ShoppingCart cart;
    int choice, orderId = 1;

    do {
        cout << "\nMenu:\n1. View Products\n2. View Shopping Cart\n3. View Orders\n4. Exit\nEnter choice: ";
        getValidInt(choice);
        
        if (choice == 1) {
            viewProducts();
            int productId;
            char addMore;
            do {
                cout << "Enter Product ID to add to cart: ";
                getValidInt(productId);
                bool found = false;
                for (auto &p : products) {
                    if (p.id == productId) {
                        cart.addItem(p);
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Invalid Product ID!\n";
                cout << "Add another product? (Y/N): ";
                addMore = getValidYN();
            } while (addMore == 'Y' || addMore == 'y');
        }
        else if (choice == 2) {
            cart.viewCart();
            if (!cart.getItems().empty()) {
                char checkout;
                cout << "Checkout? (Y/N): ";
                checkout = getValidYN();
                if (checkout == 'Y' || checkout == 'y') {
                    orders.push_back(Order(orderId++, cart));
                    cart.clear();
                    cout << "You have successfully checked out the products.\n";
                }
            }
        }
        else if (choice == 3) {
            if (orders.empty()) cout << "No orders placed yet.\n";
            else for (auto &order : orders) order.display();
        }
    } while (choice != 4);

    cout << "Thank you for shopping!\n";
    return 0;
}