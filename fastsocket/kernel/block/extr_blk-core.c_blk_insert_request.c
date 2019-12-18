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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {void* special; int /*<<< orphan*/  cmd_type; } ;

/* Variables and functions */
 int ELEVATOR_INSERT_BACK ; 
 int ELEVATOR_INSERT_FRONT ; 
 int /*<<< orphan*/  REQ_TYPE_SPECIAL ; 
 int /*<<< orphan*/  __blk_run_queue (struct request_queue*) ; 
 int /*<<< orphan*/  __elv_add_request (struct request_queue*,struct request*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_end_tag (struct request_queue*,struct request*) ; 
 scalar_t__ blk_rq_tagged (struct request*) ; 
 int /*<<< orphan*/  drive_stat_acct (struct request*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void blk_insert_request(struct request_queue *q, struct request *rq,
			int at_head, void *data)
{
	int where = at_head ? ELEVATOR_INSERT_FRONT : ELEVATOR_INSERT_BACK;
	unsigned long flags;

	/*
	 * tell I/O scheduler that this isn't a regular read/write (ie it
	 * must not attempt merges on this) and that it acts as a soft
	 * barrier
	 */
	rq->cmd_type = REQ_TYPE_SPECIAL;

	rq->special = data;

	spin_lock_irqsave(q->queue_lock, flags);

	/*
	 * If command is tagged, release the tag
	 */
	if (blk_rq_tagged(rq))
		blk_queue_end_tag(q, rq);

	drive_stat_acct(rq, 1);
	__elv_add_request(q, rq, where, 0);
	__blk_run_queue(q);
	spin_unlock_irqrestore(q->queue_lock, flags);
}