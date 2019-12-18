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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {struct request_queue* q; struct i2o_block_request* special; } ;
struct i2o_block_request {int /*<<< orphan*/  queue; struct i2o_block_device* i2o_blk_dev; } ;
struct i2o_block_device {int /*<<< orphan*/  open_queue_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ blk_end_request (struct request*,int,int) ; 
 int /*<<< orphan*/  blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_start_queue (struct request_queue*) ; 
 int /*<<< orphan*/  i2o_block_request_free (struct i2o_block_request*) ; 
 int /*<<< orphan*/  i2o_block_sglist_free (struct i2o_block_request*) ; 
 scalar_t__ likely (struct i2o_block_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void i2o_block_end_request(struct request *req, int error,
				  int nr_bytes)
{
	struct i2o_block_request *ireq = req->special;
	struct i2o_block_device *dev = ireq->i2o_blk_dev;
	struct request_queue *q = req->q;
	unsigned long flags;

	if (blk_end_request(req, error, nr_bytes))
		if (error)
			blk_end_request_all(req, -EIO);

	spin_lock_irqsave(q->queue_lock, flags);

	if (likely(dev)) {
		dev->open_queue_depth--;
		list_del(&ireq->queue);
	}

	blk_start_queue(q);

	spin_unlock_irqrestore(q->queue_lock, flags);

	i2o_block_sglist_free(ireq);
	i2o_block_request_free(ireq);
}