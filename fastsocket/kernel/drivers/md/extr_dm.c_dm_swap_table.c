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
struct queue_limits {int dummy; } ;
struct mapped_device {int /*<<< orphan*/  suspend_lock; TYPE_1__* queue; } ;
struct dm_table {int dummy; } ;
struct TYPE_2__ {struct queue_limits limits; } ;

/* Variables and functions */
 int EINVAL ; 
 struct dm_table* ERR_PTR (int) ; 
 struct dm_table* __bind (struct mapped_device*,struct dm_table*,struct queue_limits*) ; 
 int dm_calculate_queue_limits (struct dm_table*,struct queue_limits*) ; 
 struct dm_table* dm_get_live_table (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_suspended_md (struct mapped_device*) ; 
 scalar_t__ dm_table_has_no_data_devices (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_put (struct dm_table*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct dm_table *dm_swap_table(struct mapped_device *md, struct dm_table *table)
{
	struct dm_table *live_map = NULL, *map = ERR_PTR(-EINVAL);
	struct queue_limits limits;
	int r;

	mutex_lock(&md->suspend_lock);

	/* device must be suspended */
	if (!dm_suspended_md(md))
		goto out;

	/*
	 * If the new table has no data devices, retain the existing limits.
	 * This helps multipath with queue_if_no_path if all paths disappear,
	 * then new I/O is queued based on these limits, and then some paths
	 * reappear.
	 */
	if (dm_table_has_no_data_devices(table)) {
		live_map = dm_get_live_table(md);
		if (live_map)
			limits = md->queue->limits;
		dm_table_put(live_map);
	}

	if (!live_map) {
		r = dm_calculate_queue_limits(table, &limits);
		if (r) {
			map = ERR_PTR(r);
			goto out;
		}
	}

	map = __bind(md, table, &limits);

out:
	mutex_unlock(&md->suspend_lock);
	return map;
}