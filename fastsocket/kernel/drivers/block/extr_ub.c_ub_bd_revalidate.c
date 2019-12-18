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
struct TYPE_2__ {int /*<<< orphan*/  nsec; int /*<<< orphan*/  bsize; } ;
struct ub_lun {TYPE_1__ capacity; int /*<<< orphan*/  udev; } ;
struct gendisk {int /*<<< orphan*/  queue; struct ub_lun* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_queue_logical_block_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_revalidate (int /*<<< orphan*/ ,struct ub_lun*) ; 

__attribute__((used)) static int ub_bd_revalidate(struct gendisk *disk)
{
	struct ub_lun *lun = disk->private_data;

	ub_revalidate(lun->udev, lun);

	/* XXX Support sector size switching like in sr.c */
	blk_queue_logical_block_size(disk->queue, lun->capacity.bsize);
	set_capacity(disk, lun->capacity.nsec);
	// set_disk_ro(sdkp->disk, lun->readonly);

	return 0;
}