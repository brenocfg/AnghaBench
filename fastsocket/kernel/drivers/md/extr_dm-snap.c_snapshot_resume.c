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
struct dm_target {struct dm_snapshot* private; } ;
struct dm_snapshot {int active; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  __find_snapshots_sharing_cow (struct dm_snapshot*,struct dm_snapshot**,struct dm_snapshot**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __handover_exceptions (struct dm_snapshot*,struct dm_snapshot*) ; 
 int /*<<< orphan*/  _origins_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reregister_snapshot (struct dm_snapshot*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snapshot_resume(struct dm_target *ti)
{
	struct dm_snapshot *s = ti->private;
	struct dm_snapshot *snap_src = NULL, *snap_dest = NULL;

	down_read(&_origins_lock);
	(void) __find_snapshots_sharing_cow(s, &snap_src, &snap_dest, NULL);
	if (snap_src && snap_dest) {
		down_write(&snap_src->lock);
		down_write_nested(&snap_dest->lock, SINGLE_DEPTH_NESTING);
		__handover_exceptions(snap_src, snap_dest);
		up_write(&snap_dest->lock);
		up_write(&snap_src->lock);
	}
	up_read(&_origins_lock);

	/* Now we have correct chunk size, reregister */
	reregister_snapshot(s);

	down_write(&s->lock);
	s->active = 1;
	up_write(&s->lock);
}