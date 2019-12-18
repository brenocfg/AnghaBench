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
struct request_list {int* count; int* starved; int /*<<< orphan*/  elvpriv; } ;
struct request_queue {int nr_requests; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue_flags; int /*<<< orphan*/  node; struct request_list rq; } ;
struct request {int dummy; } ;
struct io_context {int /*<<< orphan*/  nr_batch_requests; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ELV_MQUEUE_MUST ; 
 int ELV_MQUEUE_NO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  QUEUE_FLAG_ELVSWITCH ; 
 int REQ_ELVPRIV ; 
 int REQ_IO_STAT ; 
 struct request* blk_alloc_request (struct request_queue*,int,int /*<<< orphan*/ ) ; 
 int blk_queue_dead (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_full (struct request_queue*,int const) ; 
 scalar_t__ blk_queue_io_stat (struct request_queue*) ; 
 scalar_t__ blk_rq_should_init_elevator (struct bio*) ; 
 int /*<<< orphan*/  blk_set_queue_congested (struct request_queue*,int const) ; 
 int /*<<< orphan*/  blk_set_queue_full (struct request_queue*,int const) ; 
 struct io_context* current_io_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int elv_may_queue (struct request_queue*,int) ; 
 int /*<<< orphan*/  freed_request (struct request_queue*,int) ; 
 scalar_t__ ioc_batching (struct request_queue*,struct io_context*) ; 
 int /*<<< orphan*/  ioc_set_batching (struct request_queue*,struct io_context*) ; 
 int queue_congestion_on_threshold (struct request_queue*) ; 
 scalar_t__ rw_is_sync (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_block_getrq (struct request_queue*,struct bio*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct request *get_request(struct request_queue *q, int rw_flags,
				   struct bio *bio, gfp_t gfp_mask)
{
	struct request *rq = NULL;
	struct request_list *rl = &q->rq;
	struct io_context *ioc = NULL;
	const bool is_sync = rw_is_sync(rw_flags) != 0;
	int may_queue;

	if (unlikely(blk_queue_dead(q)))
		return NULL;

	may_queue = elv_may_queue(q, rw_flags);
	if (may_queue == ELV_MQUEUE_NO)
		goto rq_starved;

	if (rl->count[is_sync]+1 >= queue_congestion_on_threshold(q)) {
		if (rl->count[is_sync]+1 >= q->nr_requests) {
			ioc = current_io_context(GFP_ATOMIC, q->node);
			/*
			 * The queue will fill after this allocation, so set
			 * it as full, and mark this process as "batching".
			 * This process will be allowed to complete a batch of
			 * requests, others will be blocked.
			 */
			if (!blk_queue_full(q, is_sync)) {
				ioc_set_batching(q, ioc);
				blk_set_queue_full(q, is_sync);
			} else {
				if (may_queue != ELV_MQUEUE_MUST
						&& !ioc_batching(q, ioc)) {
					/*
					 * The queue is full and the allocating
					 * process is not a "batcher", and not
					 * exempted by the IO scheduler
					 */
					goto out;
				}
			}
		}
		blk_set_queue_congested(q, is_sync);
	}

	/*
	 * Only allow batching queuers to allocate up to 50% over the defined
	 * limit of requests, otherwise we could have thousands of requests
	 * allocated with any setting of ->nr_requests
	 */
	if (rl->count[is_sync] >= (3 * q->nr_requests / 2))
		goto out;

	rl->count[is_sync]++;
	rl->starved[is_sync] = 0;

	if (blk_rq_should_init_elevator(bio) &&
	    !test_bit(QUEUE_FLAG_ELVSWITCH, &q->queue_flags)) {
		rw_flags |= REQ_ELVPRIV;
		rl->elvpriv++;
	}

	if (blk_queue_io_stat(q))
		rw_flags |= REQ_IO_STAT;
	spin_unlock_irq(q->queue_lock);

	rq = blk_alloc_request(q, rw_flags, gfp_mask);
	if (unlikely(!rq)) {
		/*
		 * Allocation failed presumably due to memory. Undo anything
		 * we might have messed up.
		 *
		 * Allocating task should really be put onto the front of the
		 * wait queue, but this is pretty rare.
		 */
		spin_lock_irq(q->queue_lock);
		freed_request(q, rw_flags);

		/*
		 * in the very unlikely event that allocation failed and no
		 * requests for this direction was pending, mark us starved
		 * so that freeing of a request in the other direction will
		 * notice us. another possible fix would be to split the
		 * rq mempool into READ and WRITE
		 */
rq_starved:
		if (unlikely(rl->count[is_sync] == 0))
			rl->starved[is_sync] = 1;

		goto out;
	}

	/*
	 * ioc may be NULL here, and ioc_batching will be false. That's
	 * OK, if the queue is under the request limit then requests need
	 * not count toward the nr_batch_requests limit. There will always
	 * be some limit enforced by BLK_BATCH_TIME.
	 */
	if (ioc_batching(q, ioc))
		ioc->nr_batch_requests--;

	trace_block_getrq(q, bio, rw_flags & 1);
out:
	return rq;
}