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
struct request_queue {int /*<<< orphan*/  queue_lock; struct mapped_device* queuedata; } ;
struct request {int cmd_flags; } ;
struct mapped_device {int dummy; } ;
struct dm_target {TYPE_1__* type; } ;
struct dm_table {int dummy; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {scalar_t__ (* busy ) (struct dm_target*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMERR_LIMIT (char*) ; 
 int /*<<< orphan*/  EIO ; 
 int REQ_FLUSH ; 
 struct request* blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_plug_device (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_plugged (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_stopped (struct request_queue*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 struct dm_table* dm_get_live_table (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_kill_unmapped_request (struct request*,int /*<<< orphan*/ ) ; 
 struct request* dm_start_request (struct mapped_device*,struct request*) ; 
 struct dm_target* dm_table_find_target (struct dm_table*,scalar_t__) ; 
 int /*<<< orphan*/  dm_table_put (struct dm_table*) ; 
 int /*<<< orphan*/  dm_target_is_valid (struct dm_target*) ; 
 int /*<<< orphan*/  elv_queue_empty (struct request_queue*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 scalar_t__ map_request (struct dm_target*,struct request*,struct mapped_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct dm_target*) ; 

__attribute__((used)) static void dm_request_fn(struct request_queue *q)
{
	struct mapped_device *md = q->queuedata;
	struct dm_table *map = dm_get_live_table(md);
	struct dm_target *ti;
	struct request *rq, *clone;
	sector_t pos;

	/*
	 * For suspend, check blk_queue_stopped() and increment
	 * ->pending within a single queue_lock not to increment the
	 * number of in-flight I/Os after the queue is stopped in
	 * dm_suspend().
	 */
	while (!blk_queue_plugged(q) && !blk_queue_stopped(q)) {
		rq = blk_peek_request(q);
		if (!rq)
			goto plug_and_out;

		/* always use block 0 to find the target for flushes for now */
		pos = 0;
		if (!(rq->cmd_flags & REQ_FLUSH))
			pos = blk_rq_pos(rq);

		ti = dm_table_find_target(map, pos);
		if (!dm_target_is_valid(ti)) {
			/*
			 * Must perform setup, that dm_done() requires,
			 * before calling dm_kill_unmapped_request
			 */
			DMERR_LIMIT("request attempted access beyond the end of device");
			clone = dm_start_request(md, rq);
			dm_kill_unmapped_request(clone, -EIO);
			continue;
		}

		if (ti->type->busy && ti->type->busy(ti))
			goto plug_and_out;

		clone = dm_start_request(md, rq);

		spin_unlock(q->queue_lock);
		if (map_request(ti, clone, md))
			goto requeued;

		BUG_ON(!irqs_disabled());
		spin_lock(q->queue_lock);
	}

	goto out;

requeued:
	BUG_ON(!irqs_disabled());
	spin_lock(q->queue_lock);

plug_and_out:
	if (!elv_queue_empty(q))
		/* Some requests still remain, retry later */
		blk_plug_device(q);

out:
	dm_table_put(map);
}