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
struct ebitmap_node {unsigned long startbit; struct ebitmap_node* next; int /*<<< orphan*/  maps; } ;
struct ebitmap {unsigned long highbit; struct ebitmap_node* node; } ;

/* Variables and functions */
 unsigned long EBITMAP_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ebitmap_node_clr_bit (struct ebitmap_node*,unsigned long) ; 
 int /*<<< orphan*/  ebitmap_node_set_bit (struct ebitmap_node*,unsigned long) ; 
 unsigned int find_first_bit (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct ebitmap_node*) ; 
 struct ebitmap_node* kzalloc (int,int /*<<< orphan*/ ) ; 

int ebitmap_set_bit(struct ebitmap *e, unsigned long bit, int value)
{
	struct ebitmap_node *n, *prev, *new;

	prev = NULL;
	n = e->node;
	while (n && n->startbit <= bit) {
		if ((n->startbit + EBITMAP_SIZE) > bit) {
			if (value) {
				ebitmap_node_set_bit(n, bit);
			} else {
				unsigned int s;

				ebitmap_node_clr_bit(n, bit);

				s = find_first_bit(n->maps, EBITMAP_SIZE);
				if (s < EBITMAP_SIZE)
					return 0;

				/* drop this node from the bitmap */
				if (!n->next) {
					/*
					 * this was the highest map
					 * within the bitmap
					 */
					if (prev)
						e->highbit = prev->startbit
							     + EBITMAP_SIZE;
					else
						e->highbit = 0;
				}
				if (prev)
					prev->next = n->next;
				else
					e->node = n->next;
				kfree(n);
			}
			return 0;
		}
		prev = n;
		n = n->next;
	}

	if (!value)
		return 0;

	new = kzalloc(sizeof(*new), GFP_ATOMIC);
	if (!new)
		return -ENOMEM;

	new->startbit = bit - (bit % EBITMAP_SIZE);
	ebitmap_node_set_bit(new, bit);

	if (!n)
		/* this node will be the highest map within the bitmap */
		e->highbit = new->startbit + EBITMAP_SIZE;

	if (prev) {
		new->next = prev->next;
		prev->next = new;
	} else {
		new->next = e->node;
		e->node = new;
	}

	return 0;
}