#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
using namespace std;

// Structure to store donor information
struct Donor {
    string name;
    string bloodGroup;
    string contact;
};

// Blood Bank Management Class
class BloodBank {
private:
    vector<Donor> donors;
    int stock[4] = {10, 10, 10, 10}; // Stock for A, B, AB, O

public:
    void registerDonor();
    void displayStock();
    void searchBloodGroup();
    void requestBlood();
    void generateReport();
};

// Function to validate blood group
bool isValidBloodGroup(const string &group) {
    string validGroups[] = {"A", "B", "AB", "O"};
    return find(begin(validGroups), end(validGroups), group) != end(validGroups);
}

// Function to register a donor
void BloodBank::registerDonor() {
    Donor d;
    cout << "\nEnter Donor Name: ";
    cin.ignore();
    getline(cin, d.name);
    
    do {
        cout << "Enter Blood Group (A, B, AB, O): ";
        cin >> d.bloodGroup;
        transform(d.bloodGroup.begin(), d.bloodGroup.end(), d.bloodGroup.begin(), ::toupper);
    } while (!isValidBloodGroup(d.bloodGroup));
    
    cout << "Enter Contact: ";
    cin >> d.contact;
    donors.push_back(d);
    
    if (d.bloodGroup == "A") stock[0]++;
    else if (d.bloodGroup == "B") stock[1]++;
    else if (d.bloodGroup == "AB") stock[2]++;
    else if (d.bloodGroup == "O") stock[3]++;
    
    cout << "\nDonor Registered Successfully!\n";
}

// Function to display blood stock
void BloodBank::displayStock() {
    cout << "\nAvailable Blood Stock:\n";
    cout << "A : " << stock[0] << " units\n";
    cout << "B : " << stock[1] << " units\n";
    cout << "AB: " << stock[2] << " units\n";
    cout << "O : " << stock[3] << " units\n";
}

// Function to search for a blood group
void BloodBank::searchBloodGroup() {
    string group;
    cout << "\nEnter Blood Group to Search: ";
    cin >> group;
    transform(group.begin(), group.end(), group.begin(), ::toupper);
    
    if (!isValidBloodGroup(group)) {
        cout << "\nInvalid Blood Group!\n";
        return;
    }
    
    cout << "\nDonors with Blood Group " << group << ":\n";
    bool found = false;
    for (const auto &d : donors) {
        if (d.bloodGroup == group) {
            cout << "Name: " << d.name << " | Contact: " << d.contact << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No donors found for this blood group.\n";
    }
}

// Function to request blood
void BloodBank::requestBlood() {
    string group;
    cout << "\nEnter Blood Group Required: ";
    cin >> group;
    transform(group.begin(), group.end(), group.begin(), ::toupper);
    
    if (!isValidBloodGroup(group)) {
        cout << "\nInvalid Blood Group!\n";
        return;
    }
    
    int index = (group == "A") ? 0 : (group == "B") ? 1 : (group == "AB") ? 2 : 3;
    if (stock[index] > 0) {
        stock[index]--;
        cout << "\nBlood Issued Successfully! Please ensure proper documentation.\n";
    } else {
        cout << "\nSorry, Blood Not Available! Consider contacting donors.\n";
    }
}

// Function to generate report
void BloodBank::generateReport() {
    cout << "\n===== Blood Bank Report =====\n";
    cout << "Total Registered Donors: " << donors.size() << "\n";
    displayStock();
}

// Main function
int main() {
    BloodBank bb;
    int choice;
    
    do {
        cout << "\n===== Blood Bank Management System =====\n";
        cout << "1. Register Donor\n2. Display Blood Stock\n3. Search Blood Group\n4. Request Blood\n5. Generate Report\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid Input! Please enter a number.\n";
            continue;
        }
        
        switch (choice) {
            case 1: bb.registerDonor(); break;
            case 2: bb.displayStock(); break;
            case 3: bb.searchBloodGroup(); break;
            case 4: bb.requestBlood(); break;
            case 5: bb.generateReport(); break;
            case 6: cout << "\nExiting... Thank you!\n"; break;
            default: cout << "\nInvalid choice, please try again.\n";
        }
    } while (choice != 6);
    
    return 0;
}