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
typedef  scalar_t__ u64 ;
struct ulist_node {scalar_t__ val; unsigned long aux; } ;
struct ulist {int nnodes; int nodes_alloced; struct ulist_node* nodes; int /*<<< orphan*/  int_nodes; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ULIST_SIZE ; 
 struct ulist_node* krealloc (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ulist_node*,int /*<<< orphan*/ ,int) ; 

int ulist_add_merge(struct ulist *ulist, u64 val, unsigned long aux,
		    unsigned long *old_aux, gfp_t gfp_mask)
{
	int i;

	for (i = 0; i < ulist->nnodes; ++i) {
		if (ulist->nodes[i].val == val) {
			if (old_aux)
				*old_aux = ulist->nodes[i].aux;
			return 0;
		}
	}

	if (ulist->nnodes >= ulist->nodes_alloced) {
		u64 new_alloced = ulist->nodes_alloced + 128;
		struct ulist_node *new_nodes;
		void *old = NULL;

		/*
		 * if nodes_alloced == ULIST_SIZE no memory has been allocated
		 * yet, so pass NULL to krealloc
		 */
		if (ulist->nodes_alloced > ULIST_SIZE)
			old = ulist->nodes;

		new_nodes = krealloc(old, sizeof(*new_nodes) * new_alloced,
				     gfp_mask);
		if (!new_nodes)
			return -ENOMEM;

		if (!old)
			memcpy(new_nodes, ulist->int_nodes,
			       sizeof(ulist->int_nodes));

		ulist->nodes = new_nodes;
		ulist->nodes_alloced = new_alloced;
	}
	ulist->nodes[ulist->nnodes].val = val;
	ulist->nodes[ulist->nnodes].aux = aux;
	++ulist->nnodes;

	return 1;
}