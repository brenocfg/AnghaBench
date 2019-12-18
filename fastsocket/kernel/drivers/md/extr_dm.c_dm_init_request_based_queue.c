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
struct request_queue {scalar_t__ elevator; } ;
struct mapped_device {struct request_queue* queue; } ;

/* Variables and functions */
 struct request_queue* blk_init_allocated_queue (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_lld_busy (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_prep_rq (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_softirq_done (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_init_md_queue (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_lld_busy ; 
 int /*<<< orphan*/  dm_prep_fn ; 
 int /*<<< orphan*/  dm_request_fn ; 
 int /*<<< orphan*/  dm_softirq_done ; 
 int /*<<< orphan*/  elv_register_queue (struct request_queue*) ; 

__attribute__((used)) static int dm_init_request_based_queue(struct mapped_device *md)
{
	struct request_queue *q = NULL;

	if (md->queue->elevator)
		return 1;

	/* Fully initialize the queue */
	q = blk_init_allocated_queue(md->queue, dm_request_fn, NULL);
	if (!q)
		return 0;

	md->queue = q;
	dm_init_md_queue(md);
	blk_queue_softirq_done(md->queue, dm_softirq_done);
	blk_queue_prep_rq(md->queue, dm_prep_fn);
	blk_queue_lld_busy(md->queue, dm_lld_busy);

	elv_register_queue(md->queue);

	return 1;
}