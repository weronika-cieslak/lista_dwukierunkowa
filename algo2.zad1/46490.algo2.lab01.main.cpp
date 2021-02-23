/*ALGO2 IS1 222A LAB01
  Weronika Cieślak
  cw46490@zut.edu.pl
*/

#include <iostream>
#include <time.h>

struct stored_data
{
	int int_data;
	char char_data;
	
	void generate_data()
	{
		const char letters[] = "abcdefghijklmnopqrstuvwxyz";
		this->int_data = rand() % 10000;
		this->char_data = letters[rand() % (sizeof(letters) - 1)];

	}
	
	
friend std::ostream& operator<<(std::ostream& os, const stored_data& sd)
{
		os <<"Dane przechowywane: " <<sd.int_data << " " << sd.char_data<<"\n";
		return os;
}
friend bool operator==(const stored_data &st,const stored_data&sd)
{
	if (st.int_data == sd.int_data &&st.char_data == sd.char_data)
		return true;
	else
		return false;
}
friend bool operator !=(const stored_data& st, const stored_data&sd)
{
	if (st.int_data == sd.int_data &&st.char_data == sd.char_data)
		return false;
	else
		return true;
}
friend bool operator <(const stored_data&  so1, const stored_data& so2)
{
	int diff = so1.int_data - so2.int_data;
	if (diff < 0)
		return true;
	else 
		return false;
}
};
template<typename T>
struct node
{
	T field;
	node *previous;
	node *next;
	node(T field)
	{
		this->field = field;
		this->previous = NULL;
		this->next = NULL;
	}
	
	void set_field(T field)
	{
		this->field = field;
	}
};
template<typename T>
class List {
public:
	node<T> *head;
	node<T> *tail;
	int size_of_list = 0;
	void add_at_tail(T data)
	{
		node<T> *node_to_add = new node<T>(data);
		if(head==NULL)
		{
			head = node_to_add;
   			head->previous = NULL;
    		head->next = NULL;
			tail = head;
		}
		else if (head == tail)
		{

			tail = node_to_add;
			tail->next = NULL;
			tail->previous = head;
			head->next = tail;
		}
		
		else
		{	
			tail->next = node_to_add;
			node_to_add->previous = tail;
			tail = node_to_add;
		}
		size_of_list++;
	}
	void add_element_front(T data)
	{
		node<T> *node_to_add = new node<T>(data);

		if (head == NULL) {

			head = node_to_add;

		}
		else {
			node_to_add->previous = NULL;
			node_to_add->next = head;
			head->previous = node_to_add;
			head = node_to_add;
		}
		size_of_list++;
	}
	void delete_last_element()
	{
		if (tail != NULL)
		{
			node<T> *temp = NULL;
			temp = tail;
			tail = tail->previous;
			tail->next = NULL;
			delete temp;
		}
		else if (head != NULL)
		{
			delete head;
		}
		
		size_of_list--;
	}
	void delete_first_element()
	{
		if (head != NULL)
		{
			node<T> *current = head;
			head = head->next;

			delete current;
			size_of_list--;
		}
		else
			printf("Brak elementow na liscie\n");
	}

	node<T> *find_node_by_index(int index)
	{
		int current_index = 0;
		node<T> *current = head;
		while (current_index != index && current != NULL)
		{
			current = current->next;
			current_index++;
		}
		
		return current;
	}

	T get(int index)
	{
		node<T> *current = find_node_by_index(index);
		if (current == NULL)
		{
			printf("Zly indeks, nie ma elementu o takim indeksie\nZostanie wyswietlony 1 element\n");
			return (head->field);
		}
		return current->field;
	}
	void replace_data(T data,int index)
	{
		int current_index = 0;
		node<T> *current = find_node_by_index(index);

		if (current == NULL)
		{
			//printf("Nie ma elementu o takim indeksie!\n");

		}
		if (current != NULL)
		{
			std::cout << "Podmieniamy ten element: " << (current->field) << "\n";
			current->set_field(data);			
		}

	}
	void clear()
	{
		node<T>* temp;
		while(head != NULL) 
		{
			
		temp = head;
		head = head->next;
		temp->previous = NULL;
		delete(temp);
		
		}

		size_of_list = 0;
	}
	node<T> *search_element(T data)
	{
		node<T> *current = head;
		while (current->field != data)
		{
			
			current = current->next;
			
			if (current==NULL)
			{
				//std::cout << "Nie ma elementu z takimi danymi!\n";

				
				return current;
			}
			
		}
		if (current->field == data)
		{
			//std::cout << "Znalezione element z takimi danymi: " << (current->field) << "\n";
			return current;
		}

	}
	void search_and_delete(T data)
	{
		node<T> *current = search_element(data);
		
		if (current == NULL)
		{
			std::cout << "Nie ma elementu z takimi danymi!\n";
			
		}
		else {
			node<T> *temp = NULL;
			temp = current;
			current = current->previous;
			current->next = current->next->next;
			delete temp;
		}
	}
	void sort()
	{
		node<T> *it_1 = NULL;
		node<T> *it_2 = NULL;
		T data;
		T data1;
		for (it_1 = head; it_1 != tail->next; it_1 = it_1->next)
		{
			for (it_2 = head; it_2 != tail->next; it_2 = it_2->next)
			{
				if (it_1->field < it_2->field)
				{
					data = it_1->field;
					data1 = it_2->field;
					it_1->set_field(data1);
					it_2->set_field(data);
					
				}
			}
		}
	}
	void add_element_with_sequence(T data)
	{
		
		this->add_element_front(data);
		this->sort();
	}
	void display_list()
	{
		std::cout << "Liczba przechowywanych elementow: " << size_of_list << "\n";
		for (int i = 0; i < size_of_list; i++)
		{
			std::cout << this->get(i) << "\n";
		}
	}
};
int main()
{
	srand(time(NULL));
	List <stored_data>* list = new List <stored_data>();
	
	for (int j = 0; j < 5; j++)
	{
		
		clock_t t1 = clock();
		for (int i = 0; i <3 ; i++)
		{
			stored_data* so = new stored_data;
			so->generate_data();
			list -> add_at_tail(*so);

			delete so;
		}				clock_t t2 = clock();
	
		t1 = clock();
		std::cout <<"t1 "<< t1 << "\n";
		list->display_list();
		for (int k = 0; k < 3; k++)
		{
			stored_data* so1 = new stored_data;
			so1->generate_data();
			list->search_and_delete(*so1);
		}
		
		t2 = clock();		std::cout <<"t2 "<< t2 << "\n";
		list->display_list();
		list->clear();
	}

	
	delete list;
	return(0);
	
 

	
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
