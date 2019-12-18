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
typedef  int (* walktree_f_t ) (struct radix_node*,void*) ;
struct radix_node_head {int rnh_cnt; struct radix_node* rnh_treetop; } ;
struct radix_node {scalar_t__ rn_bit; int rn_flags; struct radix_node* rn_dupedkey; struct radix_node* rn_left; struct radix_node* rn_right; struct radix_node* rn_parent; } ;

/* Variables and functions */
 int RNF_ROOT ; 
 int stub1 (struct radix_node*,void*) ; 

__attribute__((used)) static int
rn_walktree(struct radix_node_head *h, walktree_f_t *f, void *w)
{
	int error;
	struct radix_node *base, *next;
	struct radix_node *rn;
	int rnh_cnt;

	/*
	 * This gets complicated because we may delete the node while
	 * applying the function f to it; we cannot simply use the next
	 * leaf as the successor node in advance, because that leaf may
	 * be removed as well during deletion when it is a clone of the
	 * current node.  When that happens, we would end up referring
	 * to an already-freed radix node as the successor node.  To get
	 * around this issue, if we detect that the radix tree has changed
	 * in dimension (smaller than before), we simply restart the walk
	 * from the top of tree.
	 */
restart:
	rn = h->rnh_treetop;
	rnh_cnt = h->rnh_cnt;

	/* First time through node, go left */
	while (rn->rn_bit >= 0)
		rn = rn->rn_left;
	for (;;) {
		base = rn;
		/* If at right child go back up, otherwise, go right */
		while (rn->rn_parent->rn_right == rn &&
		    (rn->rn_flags & RNF_ROOT) == 0)
			rn = rn->rn_parent;
		/* Find the next *leaf* to start from */
		for (rn = rn->rn_parent->rn_right; rn->rn_bit >= 0;)
			rn = rn->rn_left;
		next = rn;
		/* Process leaves */
		while ((rn = base) != NULL) {
			base = rn->rn_dupedkey;
			if (!(rn->rn_flags & RNF_ROOT)
			    && (error = (*f)(rn, w)))
				return (error);
		}
		/* If one or more nodes got deleted, restart from top */
		if (h->rnh_cnt < rnh_cnt)
			goto restart;
		rn = next;
		if (rn->rn_flags & RNF_ROOT)
			return (0);
	}
	/* NOTREACHED */
}