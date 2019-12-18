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
struct request_queue {int /*<<< orphan*/  queue_lock; TYPE_1__* elevator; } ;
struct as_io_context {scalar_t__ ttime_samples; int /*<<< orphan*/  state; } ;
struct as_data {scalar_t__ antic_status; int exit_prob; int exit_no_coop; TYPE_2__* io_context; int /*<<< orphan*/  antic_work; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; struct as_io_context* aic; } ;
struct TYPE_3__ {struct as_data* elevator_data; } ;

/* Variables and functions */
 scalar_t__ ANTIC_FINISHED ; 
 scalar_t__ ANTIC_WAIT_NEXT ; 
 scalar_t__ ANTIC_WAIT_REQ ; 
 int /*<<< orphan*/  AS_TASK_RUNNING ; 
 int /*<<< orphan*/  kblockd_schedule_work (struct request_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void as_antic_timeout(unsigned long data)
{
	struct request_queue *q = (struct request_queue *)data;
	struct as_data *ad = q->elevator->elevator_data;
	unsigned long flags;

	spin_lock_irqsave(q->queue_lock, flags);
	if (ad->antic_status == ANTIC_WAIT_REQ
			|| ad->antic_status == ANTIC_WAIT_NEXT) {
		struct as_io_context *aic;
		spin_lock(&ad->io_context->lock);
		aic = ad->io_context->aic;

		ad->antic_status = ANTIC_FINISHED;
		kblockd_schedule_work(q, &ad->antic_work);

		if (aic->ttime_samples == 0) {
			/* process anticipated on has exited or timed out*/
			ad->exit_prob = (7*ad->exit_prob + 256)/8;
		}
		if (!test_bit(AS_TASK_RUNNING, &aic->state)) {
			/* process not "saved" by a cooperating request */
			ad->exit_no_coop = (7*ad->exit_no_coop + 256)/8;
		}
		spin_unlock(&ad->io_context->lock);
	}
	spin_unlock_irqrestore(q->queue_lock, flags);
}