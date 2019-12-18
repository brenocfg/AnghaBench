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
struct request {int /*<<< orphan*/  queuelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_RQ_MERGED ; 
 int /*<<< orphan*/  RQ_SET_STATE (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_put_io_context (struct request*) ; 
 int /*<<< orphan*/  as_remove_queued_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rq_fifo_time (struct request*) ; 
 int /*<<< orphan*/  rq_set_fifo_time (struct request*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void as_merged_requests(struct request_queue *q, struct request *req,
			 	struct request *next)
{
	/*
	 * if next expires before rq, assign its expire time to arq
	 * and move into next position (next will be deleted) in fifo
	 */
	if (!list_empty(&req->queuelist) && !list_empty(&next->queuelist)) {
		if (time_before(rq_fifo_time(next), rq_fifo_time(req))) {
			list_move(&req->queuelist, &next->queuelist);
			rq_set_fifo_time(req, rq_fifo_time(next));
		}
	}

	/*
	 * kill knowledge of next, this one is a goner
	 */
	as_remove_queued_request(q, next);
	as_put_io_context(next);

	RQ_SET_STATE(next, AS_RQ_MERGED);
}