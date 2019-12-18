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
struct request {int dummy; } ;
struct dasd_ccw_req {scalar_t__ callback_data; struct dasd_block* block; } ;
struct dasd_block {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  request_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  blk_requeue_request (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int _dasd_requeue_request(struct dasd_ccw_req *cqr)
{
	struct dasd_block *block = cqr->block;
	struct request *req;
	unsigned long flags;

	if (!block)
		return -EINVAL;
	spin_lock_irqsave(&block->queue_lock, flags);
	req = (struct request *) cqr->callback_data;
	blk_requeue_request(block->request_queue, req);
	spin_unlock_irqrestore(&block->queue_lock, flags);

	return 0;
}