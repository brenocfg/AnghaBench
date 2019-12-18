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
struct r5conf {int raid_disks; int /*<<< orphan*/  chunk_sectors; int /*<<< orphan*/  algorithm; TYPE_1__* disks; int /*<<< orphan*/  device_lock; } ;
struct mddev {scalar_t__ delta_disks; scalar_t__ reshape_backwards; int /*<<< orphan*/  reshape_position; int /*<<< orphan*/  chunk_sectors; int /*<<< orphan*/  layout; int /*<<< orphan*/  degraded; int /*<<< orphan*/  gendisk; int /*<<< orphan*/  array_sectors; int /*<<< orphan*/  recovery; struct r5conf* private; } ;
struct md_rdev {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct md_rdev* replacement; struct md_rdev* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 int /*<<< orphan*/  MaxSector ; 
 int /*<<< orphan*/  calc_degraded (struct r5conf*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_set_array_sectors (struct mddev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid5_size (struct mddev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revalidate_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid5_finish_reshape(struct mddev *mddev)
{
	struct r5conf *conf = mddev->private;

	if (!test_bit(MD_RECOVERY_INTR, &mddev->recovery)) {

		if (mddev->delta_disks > 0) {
			md_set_array_sectors(mddev, raid5_size(mddev, 0, 0));
			set_capacity(mddev->gendisk, mddev->array_sectors);
			revalidate_disk(mddev->gendisk);
		} else {
			int d;
			spin_lock_irq(&conf->device_lock);
			mddev->degraded = calc_degraded(conf);
			spin_unlock_irq(&conf->device_lock);
			for (d = conf->raid_disks ;
			     d < conf->raid_disks - mddev->delta_disks;
			     d++) {
				struct md_rdev *rdev = conf->disks[d].rdev;
				if (rdev)
					clear_bit(In_sync, &rdev->flags);
				rdev = conf->disks[d].replacement;
				if (rdev)
					clear_bit(In_sync, &rdev->flags);
			}
		}
		mddev->layout = conf->algorithm;
		mddev->chunk_sectors = conf->chunk_sectors;
		mddev->reshape_position = MaxSector;
		mddev->delta_disks = 0;
		mddev->reshape_backwards = 0;
	}
}