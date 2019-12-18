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
struct r5conf {int raid_disks; int /*<<< orphan*/  device_lock; struct disk_info* disks; } ;
struct mddev {int /*<<< orphan*/  degraded; struct r5conf* private; } ;
struct disk_info {TYPE_2__* rdev; TYPE_1__* replacement; } ;
struct TYPE_4__ {scalar_t__ recovery_offset; int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {scalar_t__ recovery_offset; int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  calc_degraded (struct r5conf*) ; 
 int /*<<< orphan*/  print_raid5_conf (struct r5conf*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raid5_spare_active(struct mddev *mddev)
{
	int i;
	struct r5conf *conf = mddev->private;
	struct disk_info *tmp;
	int count = 0;
	unsigned long flags;

	for (i = 0; i < conf->raid_disks; i++) {
		tmp = conf->disks + i;
		if (tmp->replacement
		    && tmp->replacement->recovery_offset == MaxSector
		    && !test_bit(Faulty, &tmp->replacement->flags)
		    && !test_and_set_bit(In_sync, &tmp->replacement->flags)) {
			/* Replacement has just become active. */
			if (!tmp->rdev
			    || !test_and_clear_bit(In_sync, &tmp->rdev->flags))
				count++;
			if (tmp->rdev) {
				/* Replaced device not technically faulty,
				 * but we need to be sure it gets removed
				 * and never re-added.
				 */
				set_bit(Faulty, &tmp->rdev->flags);
				sysfs_notify_dirent_safe(
					tmp->rdev->sysfs_state);
			}
			sysfs_notify_dirent_safe(tmp->replacement->sysfs_state);
		} else if (tmp->rdev
		    && tmp->rdev->recovery_offset == MaxSector
		    && !test_bit(Faulty, &tmp->rdev->flags)
		    && !test_and_set_bit(In_sync, &tmp->rdev->flags)) {
			count++;
			sysfs_notify_dirent_safe(tmp->rdev->sysfs_state);
		}
	}
	spin_lock_irqsave(&conf->device_lock, flags);
	mddev->degraded = calc_degraded(conf);
	spin_unlock_irqrestore(&conf->device_lock, flags);
	print_raid5_conf(conf);
	return count;
}