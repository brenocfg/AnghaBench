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
struct llist_node {struct llist_node* next; } ;
struct llist_head {struct llist_node* first; } ;

/* Variables and functions */
 struct llist_node* cmpxchg (struct llist_node**,struct llist_node*,struct llist_node*) ; 

struct llist_node *llist_del_first(struct llist_head *head)
{
	struct llist_node *entry, *old_entry, *next;

	entry = head->first;
	for (;;) {
		if (entry == NULL)
			return NULL;
		old_entry = entry;
		next = entry->next;
		entry = cmpxchg(&head->first, old_entry, next);
		if (entry == old_entry)
			break;
	}

	return entry;
}