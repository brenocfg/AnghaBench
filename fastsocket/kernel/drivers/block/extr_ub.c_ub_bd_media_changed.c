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
struct ub_lun {int changed; int /*<<< orphan*/  udev; int /*<<< orphan*/  removable; } ;
struct gendisk {struct ub_lun* private_data; } ;

/* Variables and functions */
 scalar_t__ ub_sync_tur (int /*<<< orphan*/ ,struct ub_lun*) ; 

__attribute__((used)) static int ub_bd_media_changed(struct gendisk *disk)
{
	struct ub_lun *lun = disk->private_data;

	if (!lun->removable)
		return 0;

	/*
	 * We clean checks always after every command, so this is not
	 * as dangerous as it looks. If the TEST_UNIT_READY fails here,
	 * the device is actually not ready with operator or software
	 * intervention required. One dangerous item might be a drive which
	 * spins itself down, and come the time to write dirty pages, this
	 * will fail, then block layer discards the data. Since we never
	 * spin drives up, such devices simply cannot be used with ub anyway.
	 */
	if (ub_sync_tur(lun->udev, lun) != 0) {
		lun->changed = 1;
		return 1;
	}

	return lun->changed;
}