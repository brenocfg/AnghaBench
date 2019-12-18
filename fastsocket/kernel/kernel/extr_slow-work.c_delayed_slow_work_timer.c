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
struct slow_work {TYPE_1__ link; int /*<<< orphan*/  flags; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLOW_WORK_CANCELLING ; 
 int /*<<< orphan*/  SLOW_WORK_DELAYED ; 
 int /*<<< orphan*/  SLOW_WORK_ENQ_DEFERRED ; 
 int /*<<< orphan*/  SLOW_WORK_EXECUTING ; 
 int /*<<< orphan*/  SLOW_WORK_VERY_SLOW ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add_tail (TYPE_1__*,struct list_head*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slow_work_mark_time (struct slow_work*) ; 
 int /*<<< orphan*/  slow_work_put_ref (struct slow_work*) ; 
 struct list_head slow_work_queue ; 
 int /*<<< orphan*/  slow_work_queue_lock ; 
 int /*<<< orphan*/  slow_work_queue_waits_for_occupation ; 
 int /*<<< orphan*/  slow_work_thread_wq ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct list_head vslow_work_queue ; 
 int /*<<< orphan*/  vslow_work_queue_waits_for_occupation ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delayed_slow_work_timer(unsigned long data)
{
	wait_queue_head_t *wfo_wq;
	struct list_head *queue;
	struct slow_work *work = (struct slow_work *) data;
	unsigned long flags;
	bool queued = false, put = false, first = false;

	if (test_bit(SLOW_WORK_VERY_SLOW, &work->flags)) {
		wfo_wq = &vslow_work_queue_waits_for_occupation;
		queue = &vslow_work_queue;
	} else {
		wfo_wq = &slow_work_queue_waits_for_occupation;
		queue = &slow_work_queue;
	}

	spin_lock_irqsave(&slow_work_queue_lock, flags);
	if (likely(!test_bit(SLOW_WORK_CANCELLING, &work->flags))) {
		clear_bit(SLOW_WORK_DELAYED, &work->flags);

		if (test_bit(SLOW_WORK_EXECUTING, &work->flags)) {
			/* we discard the reference the timer was holding in
			 * favour of the one the executor holds */
			set_bit(SLOW_WORK_ENQ_DEFERRED, &work->flags);
			put = true;
		} else {
			slow_work_mark_time(work);
			list_add_tail(&work->link, queue);
			queued = true;
			if (work->link.prev == queue)
				first = true;
		}
	}

	spin_unlock_irqrestore(&slow_work_queue_lock, flags);
	if (put)
		slow_work_put_ref(work);
	if (first)
		wake_up(wfo_wq);
	if (queued)
		wake_up(&slow_work_thread_wq);
}