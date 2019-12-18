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
struct TYPE_2__ {int elvpriv; int* count; int /*<<< orphan*/ * wait; } ;
struct request_queue {int* in_flight; int /*<<< orphan*/  queue_lock; TYPE_1__ rq; scalar_t__ request_fn; int /*<<< orphan*/ * flush_queue; int /*<<< orphan*/  queue_head; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __blk_run_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_throtl_drain (struct request_queue*) ; 
 int /*<<< orphan*/  elv_drain_elevator (struct request_queue*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void blk_drain_queue(struct request_queue *q, bool drain_all)
{
	int i;

	while (true) {
		bool drain = false;

		spin_lock_irq(q->queue_lock);

		elv_drain_elevator(q);
		if (drain_all)
			blk_throtl_drain(q);

		__blk_run_queue(q);

		drain |= q->rq.elvpriv;

		/*
		 * Unfortunately, requests are queued at and tracked from
		 * multiple places and there's no single counter which can
		 * be drained.  Check all the queues and counters.
		 */
		if (drain_all) {
			drain |= !list_empty(&q->queue_head);
			for (i = 0; i < 2; i++) {
				drain |= q->rq.count[i];
				drain |= q->in_flight[i];
				drain |= !list_empty(&q->flush_queue[i]);
			}
		}

		spin_unlock_irq(q->queue_lock);

		if (!drain)
			break;
		msleep(10);
	}

	/*
	 * With queue marked dead, any woken up waiter will fail the
	 * allocation path, so the wakeup chaining is lost and we're
	 * left with hung waiters. We need to wake up those waiters.
	 */
	if (q->request_fn) {
		spin_lock_irq(q->queue_lock);
		for (i = 0; i < ARRAY_SIZE(q->rq.wait); i++)
			wake_up_all(&q->rq.wait[i]);
		spin_unlock_irq(q->queue_lock);
	}

}