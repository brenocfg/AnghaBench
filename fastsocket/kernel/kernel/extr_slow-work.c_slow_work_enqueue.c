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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct TYPE_2__ {struct list_head* prev; } ;
struct slow_work {TYPE_1__ link; int /*<<< orphan*/  flags; int /*<<< orphan*/  ops; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ECANCELED ; 
 int /*<<< orphan*/  SLOW_WORK_CANCELLING ; 
 int /*<<< orphan*/  SLOW_WORK_ENQ_DEFERRED ; 
 int /*<<< orphan*/  SLOW_WORK_EXECUTING ; 
 int /*<<< orphan*/  SLOW_WORK_PENDING ; 
 int /*<<< orphan*/  SLOW_WORK_VERY_SLOW ; 
 int /*<<< orphan*/  list_add_tail (TYPE_1__*,struct list_head*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int slow_work_get_ref (struct slow_work*) ; 
 int /*<<< orphan*/  slow_work_mark_time (struct slow_work*) ; 
 struct list_head slow_work_queue ; 
 int /*<<< orphan*/  slow_work_queue_lock ; 
 int /*<<< orphan*/  slow_work_queue_waits_for_occupation ; 
 int /*<<< orphan*/  slow_work_thread_wq ; 
 scalar_t__ slow_work_user_count ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (scalar_t__) ; 
 struct list_head vslow_work_queue ; 
 int /*<<< orphan*/  vslow_work_queue_waits_for_occupation ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int slow_work_enqueue(struct slow_work *work)
{
	wait_queue_head_t *wfo_wq;
	struct list_head *queue;
	unsigned long flags;
	int ret;

	if (test_bit(SLOW_WORK_CANCELLING, &work->flags))
		return -ECANCELED;

	BUG_ON(slow_work_user_count <= 0);
	BUG_ON(!work);
	BUG_ON(!work->ops);

	/* when honouring an enqueue request, we only promise that we will run
	 * the work function in the future; we do not promise to run it once
	 * per enqueue request
	 *
	 * we use the PENDING bit to merge together repeat requests without
	 * having to disable IRQs and take the spinlock, whilst still
	 * maintaining our promise
	 */
	if (!test_and_set_bit_lock(SLOW_WORK_PENDING, &work->flags)) {
		if (test_bit(SLOW_WORK_VERY_SLOW, &work->flags)) {
			wfo_wq = &vslow_work_queue_waits_for_occupation;
			queue = &vslow_work_queue;
		} else {
			wfo_wq = &slow_work_queue_waits_for_occupation;
			queue = &slow_work_queue;
		}

		spin_lock_irqsave(&slow_work_queue_lock, flags);

		if (unlikely(test_bit(SLOW_WORK_CANCELLING, &work->flags)))
			goto cancelled;

		/* we promise that we will not attempt to execute the work
		 * function in more than one thread simultaneously
		 *
		 * this, however, leaves us with a problem if we're asked to
		 * enqueue the work whilst someone is executing the work
		 * function as simply queueing the work immediately means that
		 * another thread may try executing it whilst it is already
		 * under execution
		 *
		 * to deal with this, we set the ENQ_DEFERRED bit instead of
		 * enqueueing, and the thread currently executing the work
		 * function will enqueue the work item when the work function
		 * returns and it has cleared the EXECUTING bit
		 */
		if (test_bit(SLOW_WORK_EXECUTING, &work->flags)) {
			set_bit(SLOW_WORK_ENQ_DEFERRED, &work->flags);
		} else {
			ret = slow_work_get_ref(work);
			if (ret < 0)
				goto failed;
			slow_work_mark_time(work);
			list_add_tail(&work->link, queue);
			wake_up(&slow_work_thread_wq);

			/* if someone who could be requeued is sleeping on a
			 * thread, then ask them to yield their thread */
			if (work->link.prev == queue)
				wake_up(wfo_wq);
		}

		spin_unlock_irqrestore(&slow_work_queue_lock, flags);
	}
	return 0;

cancelled:
	ret = -ECANCELED;
failed:
	spin_unlock_irqrestore(&slow_work_queue_lock, flags);
	return ret;
}