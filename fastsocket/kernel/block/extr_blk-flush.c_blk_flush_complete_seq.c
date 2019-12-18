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
struct list_head {int dummy; } ;
struct request_queue {size_t flush_pending_idx; int /*<<< orphan*/  queue_head; struct list_head flush_data_in_flight; int /*<<< orphan*/  flush_pending_since; struct list_head* flush_queue; } ;
struct TYPE_2__ {unsigned int seq; int /*<<< orphan*/  list; } ;
struct request {TYPE_1__ flush; struct list_head queuelist; struct request_queue* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  REQ_FSEQ_DATA 131 
#define  REQ_FSEQ_DONE 130 
#define  REQ_FSEQ_POSTFLUSH 129 
#define  REQ_FSEQ_PREFLUSH 128 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int) ; 
 unsigned int blk_flush_cur_seq (struct request*) ; 
 int /*<<< orphan*/  blk_flush_restore_request (struct request*) ; 
 int blk_kick_flush (struct request_queue*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static bool blk_flush_complete_seq(struct request *rq, unsigned int seq,
				   int error)
{
	struct request_queue *q = rq->q;
	struct list_head *pending = &q->flush_queue[q->flush_pending_idx];
	bool queued = false;

	BUG_ON(rq->flush.seq & seq);
	rq->flush.seq |= seq;

	if (likely(!error))
		seq = blk_flush_cur_seq(rq);
	else
		seq = REQ_FSEQ_DONE;

	switch (seq) {
	case REQ_FSEQ_PREFLUSH:
	case REQ_FSEQ_POSTFLUSH:
		/* queue for flush */
		if (list_empty(pending))
			q->flush_pending_since = jiffies;
		list_move_tail(&rq->flush.list, pending);
		break;

	case REQ_FSEQ_DATA:
		list_move_tail(&rq->flush.list, &q->flush_data_in_flight);
		list_add(&rq->queuelist, &q->queue_head);
		queued = true;
		break;

	case REQ_FSEQ_DONE:
		/*
		 * @rq was previously adjusted by blk_flush_issue() for
		 * flush sequencing and may already have gone through the
		 * flush data request completion path.  Restore @rq for
		 * normal completion and end it.
		 */
		BUG_ON(!list_empty(&rq->queuelist));
		list_del_init(&rq->flush.list);
		blk_flush_restore_request(rq);
		__blk_end_request_all(rq, error);
		break;

	default:
		BUG();
	}

	return blk_kick_flush(q) | queued;
}