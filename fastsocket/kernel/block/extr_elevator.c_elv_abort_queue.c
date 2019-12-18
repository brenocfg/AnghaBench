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
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct request_queue {TYPE_1__ queue_head; } ;
struct request {int /*<<< orphan*/  cmd_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  REQ_QUIET ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_abort_flushes (struct request_queue*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 struct request* list_entry_rq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_block_rq_abort (struct request_queue*,struct request*) ; 

void elv_abort_queue(struct request_queue *q)
{
	struct request *rq;

	blk_abort_flushes(q);

	while (!list_empty(&q->queue_head)) {
		rq = list_entry_rq(q->queue_head.next);
		rq->cmd_flags |= REQ_QUIET;
		trace_block_rq_abort(q, rq);
		/*
		 * Mark this request as started so we don't trigger
		 * any debug logic in the end I/O path.
		 */
		blk_start_request(rq);
		__blk_end_request_all(rq, -EIO);
	}
}