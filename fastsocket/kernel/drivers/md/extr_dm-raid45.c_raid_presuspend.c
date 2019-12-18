#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  wq; int /*<<< orphan*/  dws_do_raid; } ;
struct TYPE_5__ {int /*<<< orphan*/  rh; struct dm_dirty_log* dl; } ;
struct raid_set {TYPE_3__ io; TYPE_2__ recover; } ;
struct dm_target {struct raid_set* private; } ;
struct dm_dirty_log {TYPE_1__* type; } ;
struct TYPE_4__ {scalar_t__ (* presuspend ) (struct dm_dirty_log*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 scalar_t__ RSRecover (struct raid_set*) ; 
 int /*<<< orphan*/  SetRSSuspend (struct raid_set*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_rh_stop_recovery (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct dm_dirty_log*) ; 
 int /*<<< orphan*/  wait_ios (struct raid_set*) ; 

__attribute__((used)) static void raid_presuspend(struct dm_target *ti)
{
	struct raid_set *rs = ti->private;
	struct dm_dirty_log *dl = rs->recover.dl;

	SetRSSuspend(rs);

	if (RSRecover(rs))
		dm_rh_stop_recovery(rs->recover.rh);

	cancel_delayed_work(&rs->io.dws_do_raid);
	flush_workqueue(rs->io.wq);
	wait_ios(rs);	/* Wait for completion of all ios being processed. */

	if (dl->type->presuspend && dl->type->presuspend(dl))
		/* FIXME: need better error handling. */
		DMWARN("log presuspend failed");
}