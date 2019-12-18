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
struct request_queue {int /*<<< orphan*/ * in_flight; } ;
struct request {int cmd_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELEVATOR_INSERT_REQUEUE ; 
 int REQ_SORTED ; 
 int REQ_STARTED ; 
 scalar_t__ blk_account_rq (struct request*) ; 
 int /*<<< orphan*/  elv_deactivate_rq (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  elv_insert (struct request_queue*,struct request*,int /*<<< orphan*/ ) ; 
 size_t rq_is_sync (struct request*) ; 

void elv_requeue_request(struct request_queue *q, struct request *rq)
{
	/*
	 * it already went through dequeue, we need to decrement the
	 * in_flight count again
	 */
	if (blk_account_rq(rq)) {
		q->in_flight[rq_is_sync(rq)]--;
		if (rq->cmd_flags & REQ_SORTED)
			elv_deactivate_rq(q, rq);
	}

	rq->cmd_flags &= ~REQ_STARTED;

	elv_insert(q, rq, ELEVATOR_INSERT_REQUEUE);
}