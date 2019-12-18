#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ left_setid; scalar_t__ right_setid; } ;
struct TYPE_3__ {scalar_t__ id; } ;
struct waitq_link {TYPE_2__ wql_link; TYPE_1__ wql_setid; } ;
struct waitq {scalar_t__ waitq_set_id; } ;

/* Variables and functions */
 scalar_t__ WQL_LINK ; 
 int WQ_ITERATE_CONTINUE ; 
 int WQ_ITERATE_INVALID ; 
 int WQ_ITERATE_UNLINKED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  wqdbg_v (char*) ; 
 struct waitq_link* wql_get_link (scalar_t__) ; 
 int /*<<< orphan*/  wql_invalidate (struct waitq_link*) ; 
 int /*<<< orphan*/  wql_put_link (struct waitq_link*) ; 
 scalar_t__ wql_type (struct waitq_link*) ; 

__attribute__((used)) static inline int waitq_maybe_remove_link(struct waitq *waitq,
					  uint64_t setid,
					  struct waitq_link *parent,
					  struct waitq_link *left,
					  struct waitq_link *right)
{
	uint64_t *wq_setid = &waitq->waitq_set_id;

	/*
	 * There are two scenarios:
	 *
	 * Scenario 1:
	 * --------------------------------------------------------------------
	 * waitq->waitq_set_id == parent
	 *
	 *         parent(LINK)
	 *           /    \
	 *          /      \
	 *         /        \
	 *  L(LINK/WQS_l)   R(LINK/WQS_r)
	 *
	 * In this scenario, we assert that the original waitq points to the
	 * parent link we were passed in.  If WQS_l (or WQS_r) is the waitq
	 * set we're looking for, we can set the corresponding parent
	 * link id (left or right) to 0.  To compress the tree, we can reset the
	 * waitq_set_id of the original waitq to point to the side of the
	 * parent that is still valid. We then discard the parent link object.
	 */
	if (*wq_setid == parent->wql_setid.id) {
		if (!left && !right) {
			/* completely invalid children */
			wql_invalidate(parent);
			wqdbg_v("S1, L+R");
			*wq_setid = 0;
			return WQ_ITERATE_INVALID;
		} else if (!left || left->wql_setid.id == setid) {
			/*
			 * left side matches we know it points either to the
			 * WQS we're unlinking, or to an invalid object:
			 * no need to invalidate it
			 */
			*wq_setid = right ? right->wql_setid.id : 0;
			wql_invalidate(parent);
			wqdbg_v("S1, L");
			return left ? WQ_ITERATE_UNLINKED : WQ_ITERATE_INVALID;
		} else if (!right || right->wql_setid.id == setid) {
			/*
			 * if right side matches we know it points either to the
			 * WQS we're unlinking, or to an invalid object:
			 * no need to invalidate it
			 */
			*wq_setid = left ? left->wql_setid.id : 0;
			wql_invalidate(parent);
			wqdbg_v("S1, R");
			return right ? WQ_ITERATE_UNLINKED : WQ_ITERATE_INVALID;
		}
	}

	/*
	 * the tree walk starts at the top-of-tree and moves down,
	 * so these are safe asserts.
	 */
	assert(left || right); /* one of them has to be valid at this point */

	/*
	 * Scenario 2:
	 * --------------------------------------------------------------------
	 * waitq->waitq_set_id == ... (OR parent)
	 *
	 *                    ...
	 *                     |
	 *                   parent
	 *                   /    \
	 *                  /      \
	 *              L(LINK)     R(LINK)
	 *               /\             /\
	 *              /  \           /  \
	 *             /    \       Rl(*)  Rr(*)
	 *         Ll(WQS)  Lr(WQS)
	 *
	 * In this scenario, a leaf node of either the left or right side
	 * could be the wait queue set we're looking to unlink. We also handle
	 * the case where one of these links is invalid.  If a leaf node is
	 * invalid or it's the set we're looking for, we can safely remove the
	 * middle link (left or right) and point the parent link directly to
	 * the remaining leaf node.
	 */
	if (left && wql_type(left) == WQL_LINK) {
		uint64_t Ll, Lr;
		struct waitq_link *linkLl, *linkLr;
		assert(left->wql_setid.id != setid);
		Ll = left->wql_link.left_setid;
		Lr = left->wql_link.right_setid;
		linkLl = wql_get_link(Ll);
		linkLr = wql_get_link(Lr);
		if (!linkLl && !linkLr) {
			/*
			 * The left object points to two invalid objects!
			 * We can invalidate the left w/o touching the parent.
			 */
			wql_invalidate(left);
			wqdbg_v("S2, Ll+Lr");
			return WQ_ITERATE_INVALID;
		} else if (!linkLl || Ll == setid) {
			/* Ll is invalid and/or the wait queue set we're looking for */
			parent->wql_link.left_setid = Lr;
			wql_invalidate(left);
			wql_put_link(linkLl);
			wql_put_link(linkLr);
			wqdbg_v("S2, Ll");
			return linkLl ? WQ_ITERATE_UNLINKED : WQ_ITERATE_INVALID;
		} else if (!linkLr || Lr == setid) {
			/* Lr is invalid and/or the wait queue set we're looking for */
			parent->wql_link.left_setid = Ll;
			wql_invalidate(left);
			wql_put_link(linkLr);
			wql_put_link(linkLl);
			wqdbg_v("S2, Lr");
			return linkLr ? WQ_ITERATE_UNLINKED : WQ_ITERATE_INVALID;
		}
		wql_put_link(linkLl);
		wql_put_link(linkLr);
	}

	if (right && wql_type(right) == WQL_LINK) {
		uint64_t Rl, Rr;
		struct waitq_link *linkRl, *linkRr;
		assert(right->wql_setid.id != setid);
		Rl = right->wql_link.left_setid;
		Rr = right->wql_link.right_setid;
		linkRl = wql_get_link(Rl);
		linkRr = wql_get_link(Rr);
		if (!linkRl && !linkRr) {
			/*
			 * The right object points to two invalid objects!
			 * We can invalidate the right w/o touching the parent.
			 */
			wql_invalidate(right);
			wqdbg_v("S2, Rl+Rr");
			return WQ_ITERATE_INVALID;
		} else if (!linkRl || Rl == setid) {
			/* Rl is invalid and/or the wait queue set we're looking for */
			parent->wql_link.right_setid = Rr;
			wql_invalidate(right);
			wql_put_link(linkRl);
			wql_put_link(linkRr);
			wqdbg_v("S2, Rl");
			return linkRl ? WQ_ITERATE_UNLINKED : WQ_ITERATE_INVALID;
		} else if (!linkRr || Rr == setid) {
			/* Rr is invalid and/or the wait queue set we're looking for */
			parent->wql_link.right_setid = Rl;
			wql_invalidate(right);
			wql_put_link(linkRl);
			wql_put_link(linkRr);
			wqdbg_v("S2, Rr");
			return linkRr ? WQ_ITERATE_UNLINKED : WQ_ITERATE_INVALID;
		}
		wql_put_link(linkRl);
		wql_put_link(linkRr);
	}

	return WQ_ITERATE_CONTINUE;
}