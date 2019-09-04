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
struct waitq {scalar_t__ waitq_set_id; scalar_t__ waitq_prepost_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_WALK_FULL_DAG_UNLOCKED ; 
 int /*<<< orphan*/  WQL_WQS ; 
 int /*<<< orphan*/  waitq_prepost_reserve_cb ; 
 int /*<<< orphan*/  walk_waitq_links (int /*<<< orphan*/ ,struct waitq*,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int waitq_count_prepost_reservation(struct waitq *waitq, int extra, int keep_locked)
{
	int npreposts = 0;

	/*
	 * If the waitq is not currently part of a set, and we're not asked to
	 * keep the waitq locked then we'll want to have 3 in reserve
	 * just-in-case it becomes part of a set while we unlock and reserve.
	 * We may need up to 1 object for the waitq, and 2 for the set.
	 */
	if (waitq->waitq_set_id == 0) {
		npreposts = 3;
	} else {
		/* this queue has never been preposted before */
		if (waitq->waitq_prepost_id == 0)
			npreposts = 3;

		/*
		 * Walk the set of table linkages associated with this waitq
		 * and count the worst-case number of prepost objects that
		 * may be needed during a wakeup_all. We can walk this without
		 * locking each set along the way because the table-based IDs
		 * disconnect us from the set pointers themselves, and the
		 * table walking is careful to read the setid values only once.
		 * Locking each set up the chain also doesn't guarantee that
		 * their membership won't change between the time we unlock
		 * that set and when we actually go to prepost, so our
		 * situation is no worse than before and we've alleviated lock
		 * contention on any sets to which this waitq belongs.
		 */
		(void)walk_waitq_links(LINK_WALK_FULL_DAG_UNLOCKED,
				       waitq, waitq->waitq_set_id,
				       WQL_WQS, (void *)&npreposts,
				       waitq_prepost_reserve_cb);
	}

	if (extra > 0)
		npreposts += extra;

	if (npreposts == 0 && !keep_locked) {
		/*
		 * If we get here, we were asked to reserve some prepost
		 * objects for a waitq that's previously preposted, and is not
		 * currently a member of any sets. We have also been
		 * instructed to unlock the waitq when we're done. In this
		 * case, we pre-allocated enough reserved objects to handle
		 * the case where the waitq gets added to a single set when
		 * the lock is released.
		 */
		npreposts = 3;
	}

	return npreposts;
}