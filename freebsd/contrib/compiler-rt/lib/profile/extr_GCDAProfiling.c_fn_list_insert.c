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
struct fn_node {struct fn_node* next; int /*<<< orphan*/  id; int /*<<< orphan*/  fn; } ;
struct fn_list {struct fn_node* tail; struct fn_node* head; } ;
typedef  int /*<<< orphan*/  fn_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_ID ; 
 struct fn_node* malloc (int) ; 

__attribute__((used)) static void fn_list_insert(struct fn_list* list, fn_ptr fn) {
  struct fn_node* new_node = malloc(sizeof(struct fn_node));
  new_node->fn = fn;
  new_node->next = NULL;
  new_node->id = CURRENT_ID;

  if (!list->head) {
    list->head = list->tail = new_node;
  } else {
    list->tail->next = new_node;
    list->tail = new_node;
  }
}