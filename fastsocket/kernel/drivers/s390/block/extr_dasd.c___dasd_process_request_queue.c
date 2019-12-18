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
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct dasd_device {scalar_t__ state; int features; int /*<<< orphan*/  cdev; TYPE_1__* discipline; } ;
struct dasd_ccw_req {int /*<<< orphan*/  blocklist; int /*<<< orphan*/  status; void* callback_data; } ;
struct dasd_block {int /*<<< orphan*/  ccw_queue; struct request_queue* request_queue; struct dasd_device* base; } ;
struct TYPE_2__ {struct dasd_ccw_req* (* build_cp ) (struct dasd_device*,struct dasd_block*,struct request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int DASD_FEATURE_READONLY ; 
 scalar_t__ DASD_STATE_READY ; 
 int /*<<< orphan*/  DASD_STOPPED_PENDING ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  PTR_ERR (struct dasd_ccw_req*) ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_fetch_request (struct request_queue*) ; 
 struct request* blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_plugged (struct request_queue*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  dasd_block_set_timer (struct dasd_block*,int) ; 
 int /*<<< orphan*/  dasd_device_set_stop_bits (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_profile_start (struct dasd_block*,struct dasd_ccw_req*,struct request*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct dasd_ccw_req* stub1 (struct dasd_device*,struct dasd_block*,struct request*) ; 

__attribute__((used)) static void __dasd_process_request_queue(struct dasd_block *block)
{
	struct request_queue *queue;
	struct request *req;
	struct dasd_ccw_req *cqr;
	struct dasd_device *basedev;
	unsigned long flags;
	queue = block->request_queue;
	basedev = block->base;
	/* No queue ? Then there is nothing to do. */
	if (queue == NULL)
		return;

	/*
	 * We requeue request from the block device queue to the ccw
	 * queue only in two states. In state DASD_STATE_READY the
	 * partition detection is done and we need to requeue requests
	 * for that. State DASD_STATE_ONLINE is normal block device
	 * operation.
	 */
	if (basedev->state < DASD_STATE_READY) {
		while ((req = blk_fetch_request(block->request_queue)))
			__blk_end_request_all(req, -EIO);
		return;
	}
	/* Now we try to fetch requests from the request queue */
	while (!blk_queue_plugged(queue) && (req = blk_peek_request(queue))) {
		if (basedev->features & DASD_FEATURE_READONLY &&
		    rq_data_dir(req) == WRITE) {
			DBF_DEV_EVENT(DBF_ERR, basedev,
				      "Rejecting write request %p",
				      req);
			blk_start_request(req);
			__blk_end_request_all(req, -EIO);
			continue;
		}
		cqr = basedev->discipline->build_cp(basedev, block, req);
		if (IS_ERR(cqr)) {
			if (PTR_ERR(cqr) == -EBUSY)
				break;	/* normal end condition */
			if (PTR_ERR(cqr) == -ENOMEM)
				break;	/* terminate request queue loop */
			if (PTR_ERR(cqr) == -EAGAIN) {
				/*
				 * The current request cannot be build right
				 * now, we have to try later. If this request
				 * is the head-of-queue we stop the device
				 * for 1/2 second.
				 */
				if (!list_empty(&block->ccw_queue))
					break;
				spin_lock_irqsave(
					get_ccwdev_lock(basedev->cdev), flags);
				dasd_device_set_stop_bits(basedev,
							  DASD_STOPPED_PENDING);
				spin_unlock_irqrestore(
					get_ccwdev_lock(basedev->cdev), flags);
				dasd_block_set_timer(block, HZ/2);
				break;
			}
			DBF_DEV_EVENT(DBF_ERR, basedev,
				      "CCW creation failed (rc=%ld) "
				      "on request %p",
				      PTR_ERR(cqr), req);
			blk_start_request(req);
			__blk_end_request_all(req, -EIO);
			continue;
		}
		/*
		 *  Note: callback is set to dasd_return_cqr_cb in
		 * __dasd_block_start_head to cover erp requests as well
		 */
		cqr->callback_data = (void *) req;
		cqr->status = DASD_CQR_FILLED;
		blk_start_request(req);
		list_add_tail(&cqr->blocklist, &block->ccw_queue);
		dasd_profile_start(block, cqr, req);
	}
}