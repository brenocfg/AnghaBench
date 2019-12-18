#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ weight; struct TYPE_11__* parent; struct TYPE_11__** head; struct TYPE_11__* prev; TYPE_1__* next; } ;
typedef  TYPE_2__ node_t ;
typedef  int /*<<< orphan*/  huff_t ;
struct TYPE_10__ {scalar_t__ weight; TYPE_2__** head; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_ppnode (int /*<<< orphan*/ *,TYPE_2__**) ; 
 TYPE_2__** get_ppnode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  swaplist (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static void increment(huff_t* huff, node_t *node) {
	node_t *lnode;

	if (!node) {
		return;
	}

	if (node->next != NULL && node->next->weight == node->weight) {
	    lnode = *node->head;
		if (lnode != node->parent) {
			swap(huff, lnode, node);
		}
		swaplist(lnode, node);
	}
	if (node->prev && node->prev->weight == node->weight) {
		*node->head = node->prev;
	} else {
	    *node->head = NULL;
		free_ppnode(huff, node->head);
	}
	node->weight++;
	if (node->next && node->next->weight == node->weight) {
		node->head = node->next->head;
	} else { 
		node->head = get_ppnode(huff);
		*node->head = node;
	}
	if (node->parent) {
		increment(huff, node->parent);
		if (node->prev == node->parent) {
			swaplist(node, node->parent);
			if (*node->head == node) {
				*node->head = node->parent;
			}
		}
	}
}