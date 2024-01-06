//Для
//контейнера реализовать добавление, удаление, редактирование, вывод
//содержимого контейнера на экран и в файл, поиск и сортировку элементов.
//Необходимо создать удобное пользовательское меню.
//предметная облась - аналитика данных


#include <iostream>
#include<string>
#include<list>
#include<map>
#include<unordered_set>

using namespace std;
static int idcontrol = 0;

class Document {
	string dataSource;
	int data;
	int ID;

public:
	Document();
	//Document(int id) { this->data = 0; this->dataSource = '0', this->ID = 0; };
	~Document() {};


	void showDoc();
	int getID() const;
	int getData();
	string gerSource()const;

	bool operator<(const Document& other) const {
		return ID < other.ID;
	}

	bool operator==(const Document& other) const {
		return ID == other.ID;
	}
	/*friend istream& operator>>(istream& in, Document& doc);*/
	friend ostream& operator<<(ostream& out, const Document& doc);


};

struct DocumentHash {
	size_t operator()(const Document& doc) const {
		return std::hash<int>()(doc.getID()); // Пример хеширования по ID документа
	}
};

Document::Document()
{
	string s; int data;
	cout << "\nenter data: ";
	cin >> data;
	this->data = data;
	cout << "\nenter source: ";
	cin >> s;
	this->dataSource = s;
	idcontrol++;
	this->ID = idcontrol;
}


void Document::showDoc() {
	cout << "ID - " << this->ID << endl;
	cout << "dataSource - " << this->dataSource << endl;
	cout << "data - " << this->data << endl;
}

int Document::getID() const {
	return ID;
}

int Document::getData() {
	return data;
}

string Document::gerSource() const {
	return dataSource;
}
//
//istream& operator>>(istream& in, Document& doc) {
//	cout << "Enter  name: ";
//	in.ignore();
//	getline(in, doc.dataSource);
//	
//	cout << "Enter data: ";
//	in >> doc.data;
//
//	//app.setId();
//
//	return in;
//}

ostream& operator<<(ostream& out, const Document& doc) {
	out << "Doc ID: " << doc.getID() << endl;
	out << "Datasource: " << doc.dataSource << endl;
	out << "Data: " << doc.data << endl;


	return out;
}






void addDoc(list<Document>& docList, map<int, Document>& docMap, unordered_set<Document, DocumentHash>& docSet) {
	Document newDoc;
	docList.push_back(newDoc);
	docMap.insert(pair<int, Document>(newDoc.getID(), newDoc));
	docSet.insert(newDoc);
}

void removeDoc(list<Document>& docList, map<int, Document>& docMap, unordered_set<Document, DocumentHash>& docSet) {
	int id;
	cout << "Enter the ID of the document to remove: ";
	cin >> id;
	docList.remove_if([id](Document& app) { return app.getID() == id; });
	//предикат для функции
	docMap.erase(id);

	unordered_set<Document>::iterator it = begin(docSet);
	for (; it != docSet.end(); ++it) {
		Document doc = *it;
		if (doc.getID() == id) {
			break;
		}
	}
	if (it != docSet.end()) {
		docSet.erase(it);
		cout << "Documet removed successfully!" << endl;
	}
	else {
		cout << "Document with ID " << id << " not found." << endl;
	}
}

void aditDoc(list<Document>& docList, map<int, Document>& docMap, unordered_set<Document, DocumentHash>& docSet) {
	int id;
	cout << "Enter the ID of the document to edit: ";
	cin >> id;

	Document document;

	Document* docToEdit = nullptr;
	for (auto& doc : docList) {
		if (doc.getID() == id) {
			docToEdit = &doc;
			break;
		}
	}
	if (docToEdit == nullptr) {
		cout << "Mobile app with ID " << id << " not found." << endl;
		return;
	}

	docSet.erase(*docToEdit);
	docSet.insert(*docToEdit);
	*docToEdit = document;
	docMap[id] = *docToEdit;
	cout << "Document edited successfully!" << endl;

}

void viewAllDocs(map<int, Document>& appMap) {
	for (const auto& pair : appMap) {
		cout << pair.second << endl;
	}

}

void searchDoc(unordered_set<Document, DocumentHash>& docSet) {
	string source;
	cout << "Enter the dataSource of the doc to search: ";
	cin >> source;
	for (auto it = docSet.begin(); it != docSet.end(); ++it) {
		if (it->gerSource() == source) {
			cout << "Document found: " << endl;
			cout << *it << endl;
			return;
		}
	}

	cout << "Document with name " << source << " not found." << endl;
}

void sortDocs(list<Document>& docList) {
	docList.sort();
	auto it = docList.end();
	--it;
	for (it; it != docList.begin(); it--) {
		it->showDoc();
	}
	it->showDoc();
}

int main()
{
	list<Document> docList;
	map<int, Document> docMap;
	unordered_set<Document, DocumentHash> docSet;
	int ID = 0;

	while (true) {
		cout << "\nChoose what you want to do:" << endl;
		cout << "1. Add document" << endl;
		cout << "2. Remove doc" << endl;
		cout << "3. Edit doc" << endl;
		cout << "4. View all documents" << endl;
		cout << "5. Search doc" << endl;
		cout << "6. Sort documents Ascending" << endl;
		cout << "0. Exit" << endl;

		int choice;
		cin >> choice;

		switch (choice) {

		case 1:
			addDoc(docList, docMap, docSet); break;

		case 2:
			removeDoc(docList, docMap, docSet); break;

		case 3:
			aditDoc(docList, docMap, docSet); break;

		case 4:
			viewAllDocs(docMap); break;

		case 5:
			searchDoc(docSet); break;
		case 6:
			sortDocs(docList); break;

		case 0:
			return 0;
		}
	}


}
