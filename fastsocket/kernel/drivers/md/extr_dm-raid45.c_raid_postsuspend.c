#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct dm_dirty_log* dl; } ;
struct raid_set {TYPE_1__ recover; } ;
struct dm_target {struct raid_set* private; } ;
struct dm_dirty_log {TYPE_2__* type; } ;
struct TYPE_4__ {scalar_t__ (* postsuspend ) (struct dm_dirty_log*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 scalar_t__ stub1 (struct dm_dirty_log*) ; 

__attribute__((used)) static void raid_postsuspend(struct dm_target *ti)
{
	struct raid_set *rs = ti->private;
	struct dm_dirty_log *dl = rs->recover.dl;

	if (dl->type->postsuspend && dl->type->postsuspend(dl))
		/* FIXME: need better error handling. */
		DMWARN("log postsuspend failed");

}