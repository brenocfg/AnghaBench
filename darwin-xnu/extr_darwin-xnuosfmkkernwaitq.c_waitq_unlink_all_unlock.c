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
typedef  scalar_t__ uint64_t ;
struct waitq {scalar_t__ waitq_set_id; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  LINK_WALK_ONE_LEVEL ; 
 scalar_t__ VM_KERNEL_UNSLIDE_OR_PERM (struct waitq*) ; 
 int /*<<< orphan*/  WQL_LINK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  waitq_clear_prepost_locked (struct waitq*) ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlink_all_cb ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 int /*<<< orphan*/  walk_waitq_links (int /*<<< orphan*/ ,struct waitq*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wqdbg_v (char*,void*) ; 

kern_return_t waitq_unlink_all_unlock(struct waitq *waitq)
{
	uint64_t old_set_id = 0;
	wqdbg_v("unlink waitq %p from all sets",
		(void *)VM_KERNEL_UNSLIDE_OR_PERM(waitq));
	assert(!waitq_irq_safe(waitq));

	/* it's not a member of any sets */
	if (waitq->waitq_set_id == 0) {
		waitq_unlock(waitq);
		return KERN_SUCCESS;
	}

	old_set_id = waitq->waitq_set_id;
	waitq->waitq_set_id = 0;

	/*
	 * invalidate the prepost entry for this waitq.
	 * This may drop and re-acquire the waitq lock, but that's OK because
	 * if it was added to another set and preposted to that set in the
	 * time we drop the lock, the state will remain consistent.
	 */
	(void)waitq_clear_prepost_locked(waitq);

	waitq_unlock(waitq);

	if (old_set_id) {
		/*
		 * Walk the link table and invalidate each LINK object that
		 * used to connect this waitq to one or more sets: this works
		 * because WQL_LINK objects are private to each wait queue
		 */
		(void)walk_waitq_links(LINK_WALK_ONE_LEVEL, waitq, old_set_id,
				       WQL_LINK, NULL, waitq_unlink_all_cb);
	}

	return KERN_SUCCESS;
}