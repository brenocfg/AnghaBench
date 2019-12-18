#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fn_node {scalar_t__ id; struct fn_node* next; } ;
struct fn_list {struct fn_node* tail; struct fn_node* head; } ;

/* Variables and functions */
 scalar_t__ CURRENT_ID ; 
 int /*<<< orphan*/  free (struct fn_node*) ; 

__attribute__((used)) static void fn_list_remove(struct fn_list* list) {
  struct fn_node* curr = list->head;
  struct fn_node* prev = NULL;
  struct fn_node* next = NULL;

  while (curr) {
    next = curr->next;

    if (curr->id == CURRENT_ID) {
      if (curr == list->head) {
        list->head = next;
      }

      if (curr == list->tail) {
        list->tail = prev;
      }

      if (prev) {
        prev->next = next;
      }

      free(curr);
    } else {
      prev = curr;
    }

    curr = next;
  }
}