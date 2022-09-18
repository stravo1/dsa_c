#include <stdio.h>
#include <stdlib.h>

typedef struct list {
  int key;
  struct list *next;
} node;

node *head = NULL;

void insert_end(int k) {

  node *new = (node *)malloc(sizeof(node)); // creating a new node
                                            // and passing the pointer to "new"
  new->key = k;     // assigning the value of key of the new node
  new->next = NULL; // assigning the value of the next pointer of new node

  if (!head) { // initialization
    head = new;
  } else {          // linked list initialized
    node *n = head; // n points to the 1st node

    while (n->next != NULL) { // until n->next is null, i.e., we reach the end
      n = n->next;            // make n point to the next node
    }
    n->next = new; // make the last node point to the new node
  }
}

void insert_first(int k) {
  if (!head) {
    insert_end(k);
    return;
  }
  node *new = (node *)malloc(sizeof(node)); // create new node
  new->key = k;
  new->next = head; // make the new point to old head => 1st node
  head = new;       // update head
}

void insert_pos(int k, int pos) {
  if (!head) {
    printf("Linked list has not yet been initialized\n");
    return;
  }
  if (pos < 1) {
    printf("Position has to be 1 and more\n");
    return;
  }
  if (pos == 1) {
    insert_first(k);
    return;
  }
  node *n = head;                     // we are already at head
  for (int i = 0; i < pos - 2; i++) { // we need to iterate, at max, pos - 2
                                      // times to reach the node before pos
    n = n->next;
    if (!n) {
      printf("Position doesn't exist!\n");
      return;
    }
  }

  node *new = (node *)malloc(sizeof(node)); // create new node
  new->key = k;                             // put the key
  new->next = n->next;

  n->next = new; // insertion complete
}

int delete_last() {
  if (!head) {
    printf("Linked list has not yet been initialized\n");
    return -1;
  }
  node *n = head;
  while (n->next->next) { // go to the 2nd last element
    n = n->next;
  }
  int val = n->next->key;
  free(n->next); // deallocate memory
  n->next = NULL;
  return val;
}

int delete_first() {
  if (!head) {
    printf("Linked list has not yet been initialized\n");
    return -1;
  }

  node *n = head;
  head = head->next; // make head point to the next node
  n->next = NULL; // make sure that the linked list can't be accessed in any way

  int val = n->key;
  free(n);
  return val;
}

int delete_pos(int pos) {
  if (!head) {
    printf("Linked list has not yet been initialized\n");
    return -1;
  }
  if (pos < 1) {
    printf("Position has to be 1 and more.\n");
    return -1;
  }

  if (pos == 1) {
    return delete_first();
  }
  node *n = head;
  for (int i = 0; i < pos - 2; i++) { // iterate pos - 2 times
    n = n->next;                      // reach the node before pos
    if (!n) {
      printf("Position doesn't exist!\n");
      return -1;
    }
  }
  node *del = n->next; // node to be deleted
  n->next = del->next; // skip a node
  del->next = NULL;    // prevent any access

  int val = del->key;

  free(del);
  return val;
}

void display() {
  if (!head) {
    printf("Linked list has not yet been initialized\n");
    return;
  }

  node *n = head;
  while (n) {
    printf("%d\t", n->key);
    n = n->next;
  }
  printf("\n");
}

int main() {
  while (1 > 0) {
    int i;
    printf("1. Insert \n2. Display \n3. Delete\n4. Exit\n");
    scanf("%d", &i);
    switch (i) {
    case 1: {
      printf("1. Front\n2. Middle\n3. End\n");
      scanf("%d", &i);
      switch (i) {
      case 1: {
        printf("Enter key: ");
        scanf("%d", &i);
        insert_first(i);
        break;
      }
      case 2: {
        int k, pos;
        printf("Enter key: ");
        scanf("%d", &k);
        printf("Enter position: ");
        scanf("%d", &pos);
        insert_pos(k, pos);
        break;
      }
      case 3: {
        printf("Enter key: ");
        scanf("%d", &i);
        insert_end(i);
        break;
      }
      default:
        printf("Choose again\n");
      }
      break;
    }
    case 2: {
      display();
      break;
    }
    case 3: {
      printf("1. Front\n2. Middle\n3. End\n");
      scanf("%d", &i);
      switch (i) {
      case 1: {
        delete_first();
        break;
      }
      case 2: {
        int pos;
        printf("Enter position: ");
        scanf("%d", &pos);
        delete_pos(pos);
        break;
      }
      case 3: {
        delete_last();
        break;
      }
      default:
        printf("Choose again\n");
      }
      break;
    }
    case 4:
      exit(1);
    default:
      printf("Choose again\n");
    }
  }
}
