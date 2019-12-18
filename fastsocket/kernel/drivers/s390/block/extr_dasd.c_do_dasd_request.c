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
struct request_queue {struct dasd_block* queuedata; } ;
struct dasd_block {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dasd_block_start_head (struct dasd_block*) ; 
 int /*<<< orphan*/  __dasd_process_request_queue (struct dasd_block*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_dasd_request(struct request_queue *queue)
{
	struct dasd_block *block;

	block = queue->queuedata;
	spin_lock(&block->queue_lock);
	/* Get new request from the block device request queue */
	__dasd_process_request_queue(block);
	/* Now check if the head of the ccw queue needs to be started. */
	__dasd_block_start_head(block);
	spin_unlock(&block->queue_lock);
}