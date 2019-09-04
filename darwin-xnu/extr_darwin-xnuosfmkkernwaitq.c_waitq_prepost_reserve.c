#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ waitq_lock_state_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ id; } ;
struct wq_prepost {TYPE_1__ wqp_prepostid; } ;
struct waitq {scalar_t__ waitq_set_id; scalar_t__ waitq_prepost_id; } ;

/* Variables and functions */
 scalar_t__ VM_KERNEL_UNSLIDE_OR_PERM (struct waitq*) ; 
 scalar_t__ WAITQ_KEEP_LOCKED ; 
 scalar_t__ WAITQ_UNLOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 int waitq_alloc_prepost_reservation (int,struct waitq*,int*,struct wq_prepost**) ; 
 int waitq_count_prepost_reservation (struct waitq*,int,int) ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 int /*<<< orphan*/  wqdbg_v (char*,void*,int) ; 

uint64_t waitq_prepost_reserve(struct waitq *waitq, int extra,
			       waitq_lock_state_t lock_state)
{
	uint64_t reserved = 0;
	uint64_t prev_setid = 0, prev_prepostid = 0;
	struct wq_prepost *wqp = NULL;
	int nalloc = 0, npreposts = 0;
	int keep_locked = (lock_state == WAITQ_KEEP_LOCKED);
	int unlocked = 0;

	wqdbg_v("Attempting to reserve prepost linkages for waitq %p (extra:%d)",
		(void *)VM_KERNEL_UNSLIDE_OR_PERM(waitq), extra);

	if (waitq == NULL && extra > 0) {
		/*
		 * Simple prepost object allocation:
		 * we'll add 2 more because the waitq might need an object,
		 * and the set itself may need a new POST object in addition
		 * to the number of preposts requested by the caller
		 */
		nalloc = waitq_alloc_prepost_reservation(extra + 2, NULL,
							 &unlocked, &wqp);
		assert(nalloc == extra + 2);
		return wqp->wqp_prepostid.id;
	}

	assert(lock_state == WAITQ_KEEP_LOCKED || lock_state == WAITQ_UNLOCK);

	assert(!waitq_irq_safe(waitq));

	waitq_lock(waitq);

	/* remember the set ID that we started with */
	prev_setid = waitq->waitq_set_id;
	prev_prepostid = waitq->waitq_prepost_id;

	/*
	 * If the waitq is not part of a set, and we're asked to
	 * keep the set locked, then we don't have to reserve
	 * anything!
	 */
	if (prev_setid == 0 && keep_locked)
		goto out;

	npreposts = waitq_count_prepost_reservation(waitq, extra, keep_locked);

	/* nothing for us to do! */
	if (npreposts == 0) {
		if (keep_locked)
			goto out;
		goto out_unlock;
	}

try_alloc:
	/* this _may_ unlock and relock the waitq! */
	nalloc = waitq_alloc_prepost_reservation(npreposts, waitq,
						 &unlocked, &wqp);

	if (!unlocked) {
		/* allocation held the waitq lock: we'd done! */
		if (keep_locked)
			goto out;
		goto out_unlock;
	}

	/*
	 * Before we return, if the allocation had to unlock the waitq, we
	 * must check one more time to see if we have enough. If not, we'll
	 * try to allocate the difference. If the caller requests it, we'll
	 * also leave the waitq locked so that the use of the pre-allocated
	 * prepost objects can be guaranteed to be enough if a wakeup_all is
	 * performed before unlocking the waitq.
	 */

	/*
	 * If the waitq is no longer associated with a set, or if the waitq's
	 * set/prepostid has not changed since we first walked its linkage,
	 * we're done.
	 */
	if ((waitq->waitq_set_id == 0) ||
	    (waitq->waitq_set_id == prev_setid &&
	     waitq->waitq_prepost_id == prev_prepostid)) {
		if (keep_locked)
			goto out;
		goto out_unlock;
	}

	npreposts = waitq_count_prepost_reservation(waitq, extra, keep_locked);

	if (npreposts > nalloc) {
		prev_setid = waitq->waitq_set_id;
		prev_prepostid = waitq->waitq_prepost_id;
		npreposts = npreposts - nalloc; /* only allocate the diff */
		goto try_alloc;
	}

	if (keep_locked)
		goto out;

out_unlock:
	waitq_unlock(waitq);
out:
	if (wqp)
		reserved = wqp->wqp_prepostid.id;

	return reserved;
}