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
struct request_queue {int /*<<< orphan*/ * in_flight; struct elevator_queue* elevator; } ;
struct request {int cmd_flags; } ;
struct elevator_queue {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* elevator_completed_req_fn ) (struct request_queue*,struct request*) ;} ;

/* Variables and functions */
 int REQ_SORTED ; 
 scalar_t__ blk_account_rq (struct request*) ; 
 size_t rq_is_sync (struct request*) ; 
 int /*<<< orphan*/  stub1 (struct request_queue*,struct request*) ; 

void elv_completed_request(struct request_queue *q, struct request *rq)
{
	struct elevator_queue *e = q->elevator;

	/*
	 * request is released from the driver, io must be done
	 */
	if (blk_account_rq(rq)) {
		q->in_flight[rq_is_sync(rq)]--;
		if ((rq->cmd_flags & REQ_SORTED) &&
		    e->ops->elevator_completed_req_fn)
			e->ops->elevator_completed_req_fn(q, rq);
	}
}