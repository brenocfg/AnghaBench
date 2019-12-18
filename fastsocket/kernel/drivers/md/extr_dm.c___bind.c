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
struct request_queue {int dummy; } ;
struct queue_limits {int dummy; } ;
struct mapped_device {int /*<<< orphan*/  map_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  immutable_target_type; struct dm_table* map; int /*<<< orphan*/  geometry; int /*<<< orphan*/  disk; struct request_queue* queue; } ;
struct dm_table {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_MERGE_IS_OPTIONAL ; 
 int /*<<< orphan*/  __bind_mempools (struct mapped_device*,struct dm_table*) ; 
 int /*<<< orphan*/  __set_size (struct mapped_device*,scalar_t__) ; 
 int /*<<< orphan*/  blk_queue_stopped (struct request_queue*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_table_event_callback (struct dm_table*,int /*<<< orphan*/ ,struct mapped_device*) ; 
 int /*<<< orphan*/  dm_table_get_immutable_target_type (struct dm_table*) ; 
 scalar_t__ dm_table_get_size (struct dm_table*) ; 
 int dm_table_merge_is_optional (struct dm_table*) ; 
 scalar_t__ dm_table_request_based (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_set_restrictions (struct dm_table*,struct request_queue*,struct queue_limits*) ; 
 int /*<<< orphan*/  event_callback ; 
 scalar_t__ get_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_queue (struct request_queue*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dm_table *__bind(struct mapped_device *md, struct dm_table *t,
			       struct queue_limits *limits)
{
	struct dm_table *old_map;
	struct request_queue *q = md->queue;
	sector_t size;
	unsigned long flags;
	int merge_is_optional;

	size = dm_table_get_size(t);

	/*
	 * Wipe any geometry if the size of the table changed.
	 */
	if (size != get_capacity(md->disk))
		memset(&md->geometry, 0, sizeof(md->geometry));

	__set_size(md, size);

	dm_table_event_callback(t, event_callback, md);

	/*
	 * The queue hasn't been stopped yet, if the old table type wasn't
	 * for request-based during suspension.  So stop it to prevent
	 * I/O mapping before resume.
	 * This must be done before setting the queue restrictions,
	 * because request-based dm may be run just after the setting.
	 */
	if (dm_table_request_based(t) && !blk_queue_stopped(q))
		stop_queue(q);

	__bind_mempools(md, t);

	merge_is_optional = dm_table_merge_is_optional(t);

	write_lock_irqsave(&md->map_lock, flags);
	old_map = md->map;
	md->map = t;
	md->immutable_target_type = dm_table_get_immutable_target_type(t);

	dm_table_set_restrictions(t, q, limits);
	if (merge_is_optional)
		set_bit(DMF_MERGE_IS_OPTIONAL, &md->flags);
	else
		clear_bit(DMF_MERGE_IS_OPTIONAL, &md->flags);
	write_unlock_irqrestore(&md->map_lock, flags);

	return old_map;
}