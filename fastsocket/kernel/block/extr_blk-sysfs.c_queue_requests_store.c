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
struct request_list {int* count; int /*<<< orphan*/ * wait; } ;
struct request_queue {unsigned long nr_requests; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  request_fn; struct request_list rq; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long BLKDEV_MIN_RQ ; 
 size_t BLK_RW_ASYNC ; 
 size_t BLK_RW_SYNC ; 
 int EINVAL ; 
 int /*<<< orphan*/  blk_clear_queue_congested (struct request_queue*,size_t) ; 
 int /*<<< orphan*/  blk_clear_queue_full (struct request_queue*,size_t) ; 
 int /*<<< orphan*/  blk_queue_congestion_threshold (struct request_queue*) ; 
 int /*<<< orphan*/  blk_set_queue_congested (struct request_queue*,size_t) ; 
 int /*<<< orphan*/  blk_set_queue_full (struct request_queue*,size_t) ; 
 int queue_congestion_off_threshold (struct request_queue*) ; 
 int queue_congestion_on_threshold (struct request_queue*) ; 
 int queue_var_store (unsigned long*,char const*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
queue_requests_store(struct request_queue *q, const char *page, size_t count)
{
	struct request_list *rl = &q->rq;
	unsigned long nr;
	int ret;

	if (!q->request_fn)
		return -EINVAL;

	ret = queue_var_store(&nr, page, count);
	if (nr < BLKDEV_MIN_RQ)
		nr = BLKDEV_MIN_RQ;

	spin_lock_irq(q->queue_lock);
	q->nr_requests = nr;
	blk_queue_congestion_threshold(q);

	if (rl->count[BLK_RW_SYNC] >= queue_congestion_on_threshold(q))
		blk_set_queue_congested(q, BLK_RW_SYNC);
	else if (rl->count[BLK_RW_SYNC] < queue_congestion_off_threshold(q))
		blk_clear_queue_congested(q, BLK_RW_SYNC);

	if (rl->count[BLK_RW_ASYNC] >= queue_congestion_on_threshold(q))
		blk_set_queue_congested(q, BLK_RW_ASYNC);
	else if (rl->count[BLK_RW_ASYNC] < queue_congestion_off_threshold(q))
		blk_clear_queue_congested(q, BLK_RW_ASYNC);

	if (rl->count[BLK_RW_SYNC] >= q->nr_requests) {
		blk_set_queue_full(q, BLK_RW_SYNC);
	} else if (rl->count[BLK_RW_SYNC]+1 <= q->nr_requests) {
		blk_clear_queue_full(q, BLK_RW_SYNC);
		wake_up(&rl->wait[BLK_RW_SYNC]);
	}

	if (rl->count[BLK_RW_ASYNC] >= q->nr_requests) {
		blk_set_queue_full(q, BLK_RW_ASYNC);
	} else if (rl->count[BLK_RW_ASYNC]+1 <= q->nr_requests) {
		blk_clear_queue_full(q, BLK_RW_ASYNC);
		wake_up(&rl->wait[BLK_RW_ASYNC]);
	}
	spin_unlock_irq(q->queue_lock);
	return ret;
}