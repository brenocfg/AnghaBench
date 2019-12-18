#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dasd_block {TYPE_1__* request_queue; int /*<<< orphan*/  request_queue_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/ * elevator; struct dasd_block* queuedata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_1__*) ; 
 TYPE_1__* blk_init_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_dasd_request ; 
 int /*<<< orphan*/  elevator_exit (int /*<<< orphan*/ *) ; 
 int elevator_init (TYPE_1__*,char*) ; 

__attribute__((used)) static int dasd_alloc_queue(struct dasd_block *block)
{
	int rc;

	block->request_queue = blk_init_queue(do_dasd_request,
					       &block->request_queue_lock);
	if (block->request_queue == NULL)
		return -ENOMEM;

	block->request_queue->queuedata = block;

	elevator_exit(block->request_queue->elevator);
	block->request_queue->elevator = NULL;
	rc = elevator_init(block->request_queue, "deadline");
	if (rc) {
		blk_cleanup_queue(block->request_queue);
		return rc;
	}
	return 0;
}