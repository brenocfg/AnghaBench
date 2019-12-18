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
typedef  int u_char ;
struct radix_node_head {struct radix_node* rnh_treetop; } ;
struct radix_node {int rn_offset; int rn_bit; int rn_bmask; scalar_t__ rn_mask; int* rn_key; int rn_flags; struct radix_node* rn_dupedkey; struct radix_mask* rn_mklist; struct radix_node* rn_parent; struct radix_node* rn_left; struct radix_node* rn_right; } ;
struct radix_mask {int rm_flags; int rm_bit; scalar_t__ rm_mask; struct radix_mask* rm_mklist; struct radix_node* rm_leaf; } ;
typedef  int /*<<< orphan*/  rn_matchf_t ;
typedef  int* caddr_t ;

/* Variables and functions */
 int RNF_NORMAL ; 
 int RNF_ROOT ; 
 scalar_t__ RN_MATCHF (struct radix_node*,int /*<<< orphan*/ *,void*) ; 
 int min (size_t,int) ; 
 scalar_t__ rn_satisfies_leaf (int*,struct radix_node*,int,int /*<<< orphan*/ *,void*) ; 
 struct radix_node* rn_search_m (int*,struct radix_node*,scalar_t__) ; 

struct radix_node *
rn_match_args(void *v_arg, struct radix_node_head *head,
    rn_matchf_t *f, void *w)
{
	caddr_t v = v_arg;
	struct radix_node *t = head->rnh_treetop, *x;
	caddr_t cp = v, cp2;
	caddr_t cplim;
	struct radix_node *saved_t, *top = t;
	int off = t->rn_offset, vlen = *(u_char *)cp, matched_off;
	int test, b, rn_bit;

	/*
	 * Open code rn_search(v, top) to avoid overhead of extra
	 * subroutine call.
	 */
	for (; t->rn_bit >= 0; ) {
		if (t->rn_bmask & cp[t->rn_offset])
			t = t->rn_right;
		else
			t = t->rn_left;
	}
	/*
	 * See if we match exactly as a host destination
	 * or at least learn how many bits match, for normal mask finesse.
	 *
	 * It doesn't hurt us to limit how many bytes to check
	 * to the length of the mask, since if it matches we had a genuine
	 * match and the leaf we have is the most specific one anyway;
	 * if it didn't match with a shorter length it would fail
	 * with a long one.  This wins big for class B&C netmasks which
	 * are probably the most common case...
	 */
	if (t->rn_mask)
		vlen = *(u_char *)t->rn_mask;
	cp += off; cp2 = t->rn_key + off; cplim = v + vlen;
	for (; cp < cplim; cp++, cp2++)
		if (*cp != *cp2)
			goto on1;
	/*
	 * This extra grot is in case we are explicitly asked
	 * to look up the default.  Ugh!
	 *
	 * Never return the root node itself, it seems to cause a
	 * lot of confusion.
	 */
	if (t->rn_flags & RNF_ROOT)
		t = t->rn_dupedkey;
	if (t == NULL || RN_MATCHF(t, f, w)) {
		return (t);
	} else {
		/*
		 * Although we found an exact match on the key,
		 * f() is looking for some other criteria as well.
		 * Continue looking as if the exact match failed.
		 */
		if (t->rn_parent->rn_flags & RNF_ROOT) {
			/* Hit the top; have to give up */
			return (NULL);
		}
		b = 0;
		goto keeplooking;
	}
on1:
	test = (*cp ^ *cp2) & 0xff; /* find first bit that differs */
	for (b = 7; (test >>= 1) > 0;)
		b--;
keeplooking:
	matched_off = cp - v;
	b += matched_off << 3;
	rn_bit = -1 - b;
	/*
	 * If there is a host route in a duped-key chain, it will be first.
	 */
	if ((saved_t = t)->rn_mask == 0)
		t = t->rn_dupedkey;
	for (; t; t = t->rn_dupedkey) {
		/*
		 * Even if we don't match exactly as a host,
		 * we may match if the leaf we wound up at is
		 * a route to a net.
		 */
		if (t->rn_flags & RNF_NORMAL) {
			if ((rn_bit <= t->rn_bit) && RN_MATCHF(t, f, w))
				return (t);
		} else if (rn_satisfies_leaf(v, t, matched_off, f, w)) {
			return (t);
		}
	}
	t = saved_t;
	/* start searching up the tree */
	do {
		struct radix_mask *m;
		t = t->rn_parent;
		m = t->rn_mklist;
		/*
		 * If non-contiguous masks ever become important
		 * we can restore the masking and open coding of
		 * the search and satisfaction test and put the
		 * calculation of "off" back before the "do".
		 */
		while (m) {
			if (m->rm_flags & RNF_NORMAL) {
				if ((rn_bit <= m->rm_bit) &&
				    RN_MATCHF(m->rm_leaf, f, w))
					return (m->rm_leaf);
			} else {
				off = min(t->rn_offset, matched_off);
				x = rn_search_m(v, t, m->rm_mask);
				while (x && x->rn_mask != m->rm_mask)
					x = x->rn_dupedkey;
				if (x && rn_satisfies_leaf(v, x, off, f, w))
					return (x);
			}
			m = m->rm_mklist;
		}
	} while (t != top);
	return (NULL);
}