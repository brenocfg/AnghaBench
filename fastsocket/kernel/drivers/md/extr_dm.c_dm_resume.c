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
struct mapped_device {int /*<<< orphan*/  suspend_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  queue; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_SUSPENDED ; 
 int EINVAL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dm_table* dm_get_live_table (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_queue_flush (struct mapped_device*) ; 
 scalar_t__ dm_request_based (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_suspended_md (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_table_get_size (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_put (struct dm_table*) ; 
 int dm_table_resume_targets (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_unplug_all (struct dm_table*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_fs (struct mapped_device*) ; 

int dm_resume(struct mapped_device *md)
{
	int r = -EINVAL;
	struct dm_table *map = NULL;

	mutex_lock(&md->suspend_lock);
	if (!dm_suspended_md(md))
		goto out;

	map = dm_get_live_table(md);
	if (!map || !dm_table_get_size(map))
		goto out;

	r = dm_table_resume_targets(map);
	if (r)
		goto out;

	dm_queue_flush(md);

	/*
	 * Flushing deferred I/Os must be done after targets are resumed
	 * so that mapping of targets can work correctly.
	 * Request-based dm is queueing the deferred I/Os in its request_queue.
	 */
	if (dm_request_based(md))
		start_queue(md->queue);

	unlock_fs(md);

	clear_bit(DMF_SUSPENDED, &md->flags);

	dm_table_unplug_all(map);
	r = 0;
out:
	dm_table_put(map);
	mutex_unlock(&md->suspend_lock);

	return r;
}