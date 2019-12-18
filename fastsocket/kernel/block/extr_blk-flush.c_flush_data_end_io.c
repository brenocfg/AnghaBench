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
struct request {struct request_queue* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_FSEQ_DATA ; 
 scalar_t__ blk_flush_complete_seq (struct request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_run_queue_async (struct request_queue*) ; 
 int elv_queue_empty (struct request_queue*) ; 

__attribute__((used)) static void flush_data_end_io(struct request *rq, int error)
{
	struct request_queue *q = rq->q;
	bool was_empty = elv_queue_empty(q);

	/*
	 * After populating an empty queue, kick it to avoid stall.  Read
	 * the comment in flush_end_io().
	 */
	if (blk_flush_complete_seq(rq, REQ_FSEQ_DATA, error) && was_empty)
		blk_run_queue_async(q);
}