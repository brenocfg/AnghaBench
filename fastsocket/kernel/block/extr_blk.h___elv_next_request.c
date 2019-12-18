#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  next; } ;
struct request_queue {scalar_t__ flush_pending_idx; scalar_t__ flush_running_idx; int flush_queue_delayed; TYPE_2__* elevator; TYPE_3__ queue_head; } ;
struct request {int dummy; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* elevator_dispatch_fn ) (struct request_queue*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  blk_queue_dead (struct request_queue*) ; 
 int /*<<< orphan*/  list_empty (TYPE_3__*) ; 
 struct request* list_entry_rq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_flush_queueable (struct request_queue*) ; 
 int /*<<< orphan*/  stub1 (struct request_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct request *__elv_next_request(struct request_queue *q)
{
	struct request *rq;

	while (1) {
		if (!list_empty(&q->queue_head)) {
			rq = list_entry_rq(q->queue_head.next);
			return rq;
		}
		/*
		 * Flush request is running and flush request isn't queueable
		 * in the drive, we can hold the queue till flush request is
		 * finished. Even we don't do this, driver can't dispatch next
		 * requests and will requeue them. And this can improve
		 * throughput too. For example, we have request flush1, write1,
		 * flush 2. flush1 is dispatched, then queue is hold, write1
		 * isn't inserted to queue. After flush1 is finished, flush2
		 * will be dispatched. Since disk cache is already clean,
		 * flush2 will be finished very soon, so looks like flush2 is
		 * folded to flush1.
		 * Since the queue is hold, a flag is set to indicate the queue
		 * should be restarted later. Please see flush_end_io() for
		 * details.
		 */
		if (q->flush_pending_idx != q->flush_running_idx &&
				!queue_flush_queueable(q)) {
			q->flush_queue_delayed = 1;
			return NULL;
		}
		if (unlikely(blk_queue_dead(q)) ||
		    !q->elevator->ops->elevator_dispatch_fn(q, 0))
			return NULL;
	}
}