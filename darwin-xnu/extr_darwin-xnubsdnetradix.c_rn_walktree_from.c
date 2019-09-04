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
typedef  int u_char ;
struct radix_node_head {int rnh_cnt; struct radix_node* rnh_treetop; } ;
struct radix_node {int rn_bit; int rn_bmask; size_t rn_offset; int rn_flags; struct radix_node* rn_dupedkey; struct radix_node* rn_left; struct radix_node* rn_right; struct radix_node* rn_parent; } ;

/* Variables and functions */
 int RNF_ROOT ; 
 int stub1 (struct radix_node*,void*) ; 

__attribute__((used)) static int
rn_walktree_from(struct radix_node_head *h, void *a, void *m, walktree_f_t *f,
    void *w)
{
	int error;
	struct radix_node *base, *next;
	u_char *xa = (u_char *)a;
	u_char *xm = (u_char *)m;
	struct radix_node *rn, *last;
	int stopping;
	int lastb;
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
	last = NULL;
	stopping = 0;
	rnh_cnt = h->rnh_cnt;

	/*
	 * rn_search_m is sort-of-open-coded here.
	 */
	for (rn = h->rnh_treetop; rn->rn_bit >= 0; ) {
		last = rn;
		if (!(rn->rn_bmask & xm[rn->rn_offset]))
			break;

		if (rn->rn_bmask & xa[rn->rn_offset])
			rn = rn->rn_right;
		else
			rn = rn->rn_left;
	}

	/*
	 * Two cases: either we stepped off the end of our mask,
	 * in which case last == rn, or we reached a leaf, in which
	 * case we want to start from the last node we looked at.
	 * Either way, last is the node we want to start from.
	 */
	rn = last;
	lastb = rn->rn_bit;

	/* First time through node, go left */
	while (rn->rn_bit >= 0)
		rn = rn->rn_left;

	while (!stopping) {
		base = rn;
		/* If at right child go back up, otherwise, go right */
		while (rn->rn_parent->rn_right == rn
		       && !(rn->rn_flags & RNF_ROOT)) {
			rn = rn->rn_parent;

			/* if went up beyond last, stop */
			if (rn->rn_bit <= lastb) {
				stopping = 1;
				/*
				 * XXX we should jump to the 'Process leaves'
				 * part, because the values of 'rn' and 'next'
				 * we compute will not be used. Not a big deal
				 * because this loop will terminate, but it is
				 * inefficient and hard to understand!
				 */
			}
		}

		/*
		 * The following code (bug fix) inherited from FreeBSD is
		 * currently disabled, because our implementation uses the
		 * RTF_PRCLONING scheme that has been abandoned in current
		 * FreeBSD release.  The scheme involves setting such a flag
		 * for the default route entry, and therefore all off-link
		 * destinations would become clones of that entry.  Enabling
		 * the following code would be problematic at this point,
		 * because the removal of default route would cause only
		 * the left-half of the tree to be traversed, leaving the
		 * right-half untouched.  If there are clones of the entry
		 * that reside in that right-half, they would not be deleted
		 * and would linger around until they expire or explicitly
		 * deleted, which is a very bad thing.
		 *
		 * This code should be uncommented only after we get rid
		 * of the RTF_PRCLONING scheme.
		 */
#if 0
		/*
		 * At the top of the tree, no need to traverse the right
		 * half, prevent the traversal of the entire tree in the
		 * case of default route.
		 */
		if (rn->rn_parent->rn_flags & RNF_ROOT)
			stopping = 1;
#endif

		/* Find the next *leaf* to start from */
		for (rn = rn->rn_parent->rn_right; rn->rn_bit >= 0;)
			rn = rn->rn_left;
		next = rn;
		/* Process leaves */
		while ((rn = base) != 0) {
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
			stopping = 1;
	}
	return 0;
}