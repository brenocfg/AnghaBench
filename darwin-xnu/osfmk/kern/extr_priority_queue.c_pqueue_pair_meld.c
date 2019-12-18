#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priority_queue_entry_t ;
typedef  int /*<<< orphan*/  priority_queue_compare_fn_t ;
struct TYPE_8__ {struct TYPE_8__* prev; struct TYPE_8__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_1__* pqueue_merge (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

priority_queue_entry_t
pqueue_pair_meld(priority_queue_entry_t elt, priority_queue_compare_fn_t cmp_fn)
{
	priority_queue_entry_t pq_meld_result = NULL;
	priority_queue_entry_t pair_list = NULL;

	assert(elt); // caller needs to check this.

	/* Phase 1: */
	/* Split the list into a set of pairs going front to back. */
	/* Hook these pairs onto an intermediary list in reverse order of traversal.*/

	do {
		/* Consider two elements at a time for pairing */
		priority_queue_entry_t pair_item_a = elt;
		priority_queue_entry_t pair_item_b = elt->next;
		if (pair_item_b == NULL) {
			/* Odd number of elements in the list; link the odd element */
			/* as it is on the intermediate list. */
			pair_item_a->prev = pair_list;
			pair_list = pair_item_a;
			break;
		}
		/* Found two elements to pair up */
		elt = pair_item_b->next;
		priority_queue_entry_t pair = pqueue_merge(pair_item_a, pair_item_b, cmp_fn);
		/* Link the pair onto the intermediary list */
		pair->prev = pair_list;
		pair_list = pair;
	} while (elt != NULL);

	/* Phase 2: Merge all the pairs in the pair_list */
	do {
		elt = pair_list->prev;
		pq_meld_result = pqueue_merge(pq_meld_result, pair_list, cmp_fn);
		pair_list = elt;
	} while (pair_list != NULL);

	return pq_meld_result;
}