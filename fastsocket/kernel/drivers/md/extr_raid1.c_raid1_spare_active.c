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
struct r1conf {int raid_disks; int /*<<< orphan*/  device_lock; TYPE_1__* mirrors; } ;
struct mddev {int degraded; struct r1conf* private; } ;
struct md_rdev {scalar_t__ recovery_offset; int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct md_rdev* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  print_conf (struct r1conf*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raid1_spare_active(struct mddev *mddev)
{
	int i;
	struct r1conf *conf = mddev->private;
	int count = 0;
	unsigned long flags;

	/*
	 * Find all failed disks within the RAID1 configuration 
	 * and mark them readable.
	 * Called under mddev lock, so rcu protection not needed.
	 */
	for (i = 0; i < conf->raid_disks; i++) {
		struct md_rdev *rdev = conf->mirrors[i].rdev;
		struct md_rdev *repl = conf->mirrors[conf->raid_disks + i].rdev;
		if (repl
		    && repl->recovery_offset == MaxSector
		    && !test_bit(Faulty, &repl->flags)
		    && !test_and_set_bit(In_sync, &repl->flags)) {
			/* replacement has just become active */
			if (!rdev ||
			    !test_and_clear_bit(In_sync, &rdev->flags))
				count++;
			if (rdev) {
				/* Replaced device not technically
				 * faulty, but we need to be sure
				 * it gets removed and never re-added
				 */
				set_bit(Faulty, &rdev->flags);
				sysfs_notify_dirent_safe(
					rdev->sysfs_state);
			}
		}
		if (rdev
		    && rdev->recovery_offset == MaxSector
		    && !test_bit(Faulty, &rdev->flags)
		    && !test_and_set_bit(In_sync, &rdev->flags)) {
			count++;
			sysfs_notify_dirent_safe(rdev->sysfs_state);
		}
	}
	spin_lock_irqsave(&conf->device_lock, flags);
	mddev->degraded -= count;
	spin_unlock_irqrestore(&conf->device_lock, flags);

	print_conf(conf);
	return count;
}