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
union map_info {struct dm_snap_tracked_chunk* ptr; } ;
struct dm_target {struct dm_snapshot* private; } ;
struct dm_snapshot {int dummy; } ;
struct dm_snap_tracked_chunk {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stop_tracking_chunk (struct dm_snapshot*,struct dm_snap_tracked_chunk*) ; 

__attribute__((used)) static int snapshot_end_io(struct dm_target *ti, struct bio *bio,
			   int error, union map_info *map_context)
{
	struct dm_snapshot *s = ti->private;
	struct dm_snap_tracked_chunk *c = map_context->ptr;

	if (c)
		stop_tracking_chunk(s, c);

	return 0;
}