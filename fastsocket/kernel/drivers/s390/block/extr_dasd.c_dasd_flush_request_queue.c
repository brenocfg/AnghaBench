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
struct dasd_block {int /*<<< orphan*/  request_queue_lock; int /*<<< orphan*/  request_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_fetch_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dasd_flush_request_queue(struct dasd_block *block)
{
	struct request *req;

	if (!block->request_queue)
		return;

	spin_lock_irq(&block->request_queue_lock);
	while ((req = blk_fetch_request(block->request_queue)))
		__blk_end_request_all(req, -EIO);
	spin_unlock_irq(&block->request_queue_lock);
}