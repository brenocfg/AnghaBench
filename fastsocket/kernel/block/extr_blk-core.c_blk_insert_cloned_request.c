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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {TYPE_2__* rq_disk; } ;
struct TYPE_3__ {scalar_t__ make_it_fail; } ;
struct TYPE_4__ {TYPE_1__ part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  ELEVATOR_INSERT_BACK ; 
 int ENODEV ; 
 int /*<<< orphan*/  __elv_add_request (struct request_queue*,struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_dead (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queued_rq (struct request*) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 scalar_t__ blk_rq_check_limits (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  drive_stat_acct (struct request*,int) ; 
 int /*<<< orphan*/  fail_make_request ; 
 scalar_t__ should_fail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int blk_insert_cloned_request(struct request_queue *q, struct request *rq)
{
	unsigned long flags;

	if (blk_rq_check_limits(q, rq))
		return -EIO;

#ifdef CONFIG_FAIL_MAKE_REQUEST
	if (rq->rq_disk && rq->rq_disk->part0.make_it_fail &&
	    should_fail(&fail_make_request, blk_rq_bytes(rq)))
		return -EIO;
#endif

	spin_lock_irqsave(q->queue_lock, flags);
	if (unlikely(blk_queue_dead(q))) {
		spin_unlock_irqrestore(q->queue_lock, flags);
		return -ENODEV;
	}

	/*
	 * Submitting request must be dequeued before calling this function
	 * because it will be linked to another request_queue
	 */
	BUG_ON(blk_queued_rq(rq));

	drive_stat_acct(rq, 1);
	__elv_add_request(q, rq, ELEVATOR_INSERT_BACK, 0);

	spin_unlock_irqrestore(q->queue_lock, flags);

	return 0;
}