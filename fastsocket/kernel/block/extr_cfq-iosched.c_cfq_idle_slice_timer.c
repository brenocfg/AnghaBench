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
struct cfq_queue {int /*<<< orphan*/  sort_list; } ;
struct cfq_data {TYPE_1__* queue; int /*<<< orphan*/  busy_queues; struct cfq_queue* active_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 scalar_t__ cfq_cfqq_must_dispatch (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_clear_cfqq_deep (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_log (struct cfq_data*,char*) ; 
 int /*<<< orphan*/  cfq_schedule_dispatch (struct cfq_data*) ; 
 int /*<<< orphan*/  cfq_slice_expired (struct cfq_data*,int) ; 
 scalar_t__ cfq_slice_used (struct cfq_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void cfq_idle_slice_timer(unsigned long data)
{
	struct cfq_data *cfqd = (struct cfq_data *) data;
	struct cfq_queue *cfqq;
	unsigned long flags;
	int timed_out = 1;

	cfq_log(cfqd, "idle timer fired");

	spin_lock_irqsave(cfqd->queue->queue_lock, flags);

	cfqq = cfqd->active_queue;
	if (cfqq) {
		timed_out = 0;

		/*
		 * We saw a request before the queue expired, let it through
		 */
		if (cfq_cfqq_must_dispatch(cfqq))
			goto out_kick;

		/*
		 * expired
		 */
		if (cfq_slice_used(cfqq))
			goto expire;

		/*
		 * only expire and reinvoke request handler, if there are
		 * other queues with pending requests
		 */
		if (!cfqd->busy_queues)
			goto out_cont;

		/*
		 * not expired and it has a request pending, let it dispatch
		 */
		if (!RB_EMPTY_ROOT(&cfqq->sort_list))
			goto out_kick;

		/*
		 * Queue depth flag is reset only when the idle didn't succeed
		 */
		cfq_clear_cfqq_deep(cfqq);
	}
expire:
	cfq_slice_expired(cfqd, timed_out);
out_kick:
	cfq_schedule_dispatch(cfqd);
out_cont:
	spin_unlock_irqrestore(cfqd->queue->queue_lock, flags);
}