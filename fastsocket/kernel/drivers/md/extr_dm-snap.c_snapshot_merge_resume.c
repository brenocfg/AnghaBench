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
struct dm_target {int /*<<< orphan*/  split_io; struct dm_snapshot* private; } ;
struct dm_snapshot {TYPE_1__* origin; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_origin_minimum_chunksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snapshot_resume (struct dm_target*) ; 
 int /*<<< orphan*/  start_merge (struct dm_snapshot*) ; 

__attribute__((used)) static void snapshot_merge_resume(struct dm_target *ti)
{
	struct dm_snapshot *s = ti->private;

	/*
	 * Handover exceptions from existing snapshot.
	 */
	snapshot_resume(ti);

	/*
	 * snapshot-merge acts as an origin, so set ti->split_io
	 */
	ti->split_io = get_origin_minimum_chunksize(s->origin->bdev);

	start_merge(s);
}