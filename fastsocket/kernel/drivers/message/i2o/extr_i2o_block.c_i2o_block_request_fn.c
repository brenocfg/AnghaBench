#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {scalar_t__ cmd_type; struct i2o_block_request* special; } ;
struct i2o_block_request {TYPE_1__* i2o_blk_dev; } ;
struct i2o_block_delayed_request {int /*<<< orphan*/  work; struct request_queue* queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_queue; } ;
struct TYPE_3__ {unsigned int open_queue_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int I2O_BLOCK_MAX_OPEN_REQUESTS ; 
 int /*<<< orphan*/  I2O_BLOCK_RETRY_TIME ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ REQ_TYPE_FS ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_plugged (struct request_queue*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  blk_stop_queue (struct request_queue*) ; 
 int /*<<< orphan*/  i2o_block_delayed_request_fn ; 
 TYPE_2__ i2o_block_driver ; 
 int /*<<< orphan*/  i2o_block_transfer (struct request*) ; 
 int /*<<< orphan*/  kfree (struct i2o_block_delayed_request*) ; 
 struct i2o_block_delayed_request* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_info (char*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2o_block_request_fn(struct request_queue *q)
{
	struct request *req;

	while (!blk_queue_plugged(q)) {
		req = blk_peek_request(q);
		if (!req)
			break;

		if (req->cmd_type == REQ_TYPE_FS) {
			struct i2o_block_delayed_request *dreq;
			struct i2o_block_request *ireq = req->special;
			unsigned int queue_depth;

			queue_depth = ireq->i2o_blk_dev->open_queue_depth;

			if (queue_depth < I2O_BLOCK_MAX_OPEN_REQUESTS) {
				if (!i2o_block_transfer(req)) {
					blk_start_request(req);
					continue;
				} else
					osm_info("transfer error\n");
			}

			if (queue_depth)
				break;

			/* stop the queue and retry later */
			dreq = kmalloc(sizeof(*dreq), GFP_ATOMIC);
			if (!dreq)
				continue;

			dreq->queue = q;
			INIT_DELAYED_WORK(&dreq->work,
					  i2o_block_delayed_request_fn);

			if (!queue_delayed_work(i2o_block_driver.event_queue,
						&dreq->work,
						I2O_BLOCK_RETRY_TIME))
				kfree(dreq);
			else {
				blk_stop_queue(q);
				break;
			}
		} else {
			blk_start_request(req);
			__blk_end_request_all(req, -EIO);
		}
	}
}