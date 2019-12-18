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
struct request_queue {int dummy; } ;
struct request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_clear_rq_complete (struct request*) ; 
 int /*<<< orphan*/  blk_delete_timer (struct request*) ; 
 int /*<<< orphan*/  blk_queue_end_tag (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  blk_queued_rq (struct request*) ; 
 scalar_t__ blk_rq_tagged (struct request*) ; 
 int /*<<< orphan*/  elv_requeue_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  trace_block_rq_requeue (struct request_queue*,struct request*) ; 

void blk_requeue_request(struct request_queue *q, struct request *rq)
{
	blk_delete_timer(rq);
	blk_clear_rq_complete(rq);
	trace_block_rq_requeue(q, rq);

	if (blk_rq_tagged(rq))
		blk_queue_end_tag(q, rq);

	BUG_ON(blk_queued_rq(rq));

	elv_requeue_request(q, rq);
}