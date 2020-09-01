#include <stdio.h>	
#include <string.h>

struct node {
	char str[255];
	struct node *next;
}*list_head;

void insert_dictionary_order(char* word);
void print_list();

int main() {
	list_head = NULL;
	printf("This is a link list demo.\nPlease enter values to insert into linked-list\nEnter . to stop entry process and view list content\n\n");

	
	char user_input[255];
	printf("Enter string(s): ");
	while (1) {
		scanf("%s", user_input);
		if (strcmp(".", user_input) == 0)
			break;

		insert_dictionary_order(user_input);
	}
	print_list();

	getchar();
	getchar();
	getchar();
	return 0;
}

void insert_dictionary_order(char* word) {
	// special case: first word
	if (list_head == NULL) {
		list_head = (struct node*)malloc(sizeof(struct node));
		memset(list_head->str, '\0', sizeof(list_head->str));
		strcpy(list_head->str, word);
		list_head->next = NULL;
		return;
	}
	// special case: replacing head of list
	if (strcmp(list_head, word) > 0) {
		// make new node to hold head content
		struct node* new_node = (struct node*)malloc(sizeof(struct node));
		strcpy(new_node->str, list_head->str);
		new_node->next = list_head->next;
		// make new node for new value 
		list_head->next = new_node;
		strcpy(list_head->str, word);
		return;
	}

	// regular cases
	struct node* iterator = list_head, *previous_node;
	previous_node = NULL;

	while (iterator != NULL) {
		// compare for place
		if (strcmp(iterator->str, word) == 0)
			return;
		if (strcmp(iterator->str, word) > 0) {
			struct node* new_node = (struct node*)malloc(sizeof(struct node));
			new_node->next = iterator;
			previous_node->next = new_node;
			// populate value
			strcpy(new_node->str, word);
			return;
		}

		// end reached
		if (iterator->next == NULL && strcmp(iterator->str, word) != 0) {
			// make new node to end of list
			iterator->next = (struct node*)malloc(sizeof(struct node));
			iterator = iterator->next;
			// populate new node and terminate list properly
			strcpy(iterator->str, word);
			iterator->next = NULL;
			return;
		}


		previous_node = iterator;
		iterator = iterator->next;
	}
}

void print_list() {
	if (list_head == NULL) {
		printf("list is empty.\n");
		return;
	}

	struct node* iterator = list_head;
	printf("List content:\n");
	int i = 1;
	while (iterator != NULL) {
		printf("%d [%s]\n", i++, iterator->str);
		iterator = iterator->next;
	}
}