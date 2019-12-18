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
struct TYPE_2__ {int* count; int* starved; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; TYPE_1__ rq; } ;
struct request {int /*<<< orphan*/  errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_fetch_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_stop_queue (struct request_queue*) ; 
 int /*<<< orphan*/  bsg_unregister_queue (struct request_queue*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void bsg_remove_queue(struct request_queue *q)
{
	struct request *req; /* block request */
	int counts; /* totals for request_list count and starved */

	if (!q)
		return;

	/* Stop taking in new requests */
	spin_lock_irq(q->queue_lock);
	blk_stop_queue(q);

	/* drain all requests in the queue */
	while (1) {
		/* need the lock to fetch a request
		 * this may fetch the same reqeust as the previous pass
		 */
		req = blk_fetch_request(q);
		/* save requests in use and starved */
		counts = q->rq.count[0] + q->rq.count[1] +
			 q->rq.starved[0] + q->rq.starved[1];
		spin_unlock_irq(q->queue_lock);
		/* any requests still outstanding? */
		if (counts == 0)
			break;

		/* This may be the same req as the previous iteration,
		 * always send the blk_end_request_all after a prefetch.
		 * It is not okay to not end the request because the
		 * prefetch started the request.
		 */
		if (req) {
			/* return -ENXIO to indicate that this queue is
			 * going away
			 */
			req->errors = -ENXIO;
			blk_end_request_all(req, -ENXIO);
		}

		msleep(200); /* allow bsg to possibly finish */
		spin_lock_irq(q->queue_lock);
	}
	bsg_unregister_queue(q);
}