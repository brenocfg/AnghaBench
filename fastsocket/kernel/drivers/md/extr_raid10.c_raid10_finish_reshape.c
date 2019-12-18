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
struct TYPE_4__ {int raid_disks; int chunk_shift; } ;
struct r10conf {TYPE_2__ geo; TYPE_1__* mirrors; } ;
struct mddev {scalar_t__ delta_disks; int chunk_sectors; scalar_t__ reshape_backwards; int /*<<< orphan*/  reshape_position; int /*<<< orphan*/  new_layout; int /*<<< orphan*/  layout; int /*<<< orphan*/  gendisk; int /*<<< orphan*/  array_sectors; int /*<<< orphan*/  resync_max_sectors; int /*<<< orphan*/  recovery; int /*<<< orphan*/  recovery_cp; struct r10conf* private; } ;
struct md_rdev {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_3__ {struct md_rdev* replacement; struct md_rdev* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  MaxSector ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_set_array_sectors (struct mddev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid10_size (struct mddev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revalidate_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid10_finish_reshape(struct mddev *mddev)
{
	struct r10conf *conf = mddev->private;

	if (test_bit(MD_RECOVERY_INTR, &mddev->recovery))
		return;

	if (mddev->delta_disks > 0) {
		sector_t size = raid10_size(mddev, 0, 0);
		md_set_array_sectors(mddev, size);
		if (mddev->recovery_cp > mddev->resync_max_sectors) {
			mddev->recovery_cp = mddev->resync_max_sectors;
			set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
		}
		mddev->resync_max_sectors = size;
		set_capacity(mddev->gendisk, mddev->array_sectors);
		revalidate_disk(mddev->gendisk);
	} else {
		int d;
		for (d = conf->geo.raid_disks ;
		     d < conf->geo.raid_disks - mddev->delta_disks;
		     d++) {
			struct md_rdev *rdev = conf->mirrors[d].rdev;
			if (rdev)
				clear_bit(In_sync, &rdev->flags);
			rdev = conf->mirrors[d].replacement;
			if (rdev)
				clear_bit(In_sync, &rdev->flags);
		}
	}
	mddev->layout = mddev->new_layout;
	mddev->chunk_sectors = 1 << conf->geo.chunk_shift;
	mddev->reshape_position = MaxSector;
	mddev->delta_disks = 0;
	mddev->reshape_backwards = 0;
}