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
struct r5conf {int raid_disks; scalar_t__ recovery_disabled; int fullsync; struct disk_info* disks; } ;
struct mddev {scalar_t__ recovery_disabled; struct r5conf* private; } ;
struct md_rdev {int saved_raid_disk; int raid_disk; int /*<<< orphan*/  flags; } ;
struct disk_info {TYPE_1__* replacement; TYPE_1__* rdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  Replacement ; 
 int /*<<< orphan*/  WantReplacement ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ has_failed (struct r5conf*) ; 
 int /*<<< orphan*/  print_raid5_conf (struct r5conf*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (TYPE_1__*,struct md_rdev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raid5_add_disk(struct mddev *mddev, struct md_rdev *rdev)
{
	struct r5conf *conf = mddev->private;
	int err = -EEXIST;
	int disk;
	struct disk_info *p;
	int first = 0;
	int last = conf->raid_disks - 1;

	if (mddev->recovery_disabled == conf->recovery_disabled)
		return -EBUSY;

	if (rdev->saved_raid_disk < 0 && has_failed(conf))
		/* no point adding a device */
		return -EINVAL;

	if (rdev->raid_disk >= 0)
		first = last = rdev->raid_disk;

	/*
	 * find the disk ... but prefer rdev->saved_raid_disk
	 * if possible.
	 */
	if (rdev->saved_raid_disk >= 0 &&
	    rdev->saved_raid_disk >= first &&
	    conf->disks[rdev->saved_raid_disk].rdev == NULL)
		first = rdev->saved_raid_disk;

	for (disk = first; disk <= last; disk++) {
		p = conf->disks + disk;
		if (p->rdev == NULL) {
			clear_bit(In_sync, &rdev->flags);
			rdev->raid_disk = disk;
			err = 0;
			if (rdev->saved_raid_disk != disk)
				conf->fullsync = 1;
			rcu_assign_pointer(p->rdev, rdev);
			goto out;
		}
	}
	for (disk = first; disk <= last; disk++) {
		p = conf->disks + disk;
		if (test_bit(WantReplacement, &p->rdev->flags) &&
		    p->replacement == NULL) {
			clear_bit(In_sync, &rdev->flags);
			set_bit(Replacement, &rdev->flags);
			rdev->raid_disk = disk;
			err = 0;
			conf->fullsync = 1;
			rcu_assign_pointer(p->replacement, rdev);
			break;
		}
	}
out:
	print_raid5_conf(conf);
	return err;
}