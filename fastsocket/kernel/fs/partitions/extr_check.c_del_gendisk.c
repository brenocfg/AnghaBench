#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hd_struct {int /*<<< orphan*/  partno; } ;
struct TYPE_5__ {int /*<<< orphan*/  holder_dir; scalar_t__ stamp; } ;
struct gendisk {int /*<<< orphan*/ * driverfs_dev; int /*<<< orphan*/  slave_dir; TYPE_1__ part0; int /*<<< orphan*/  flags; } ;
struct disk_part_iter {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 int DISK_PITER_INCL_EMPTY ; 
 int DISK_PITER_REVERSE ; 
 int /*<<< orphan*/  GENHD_FL_UP ; 
 int /*<<< orphan*/  blk_free_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_depr ; 
 int /*<<< orphan*/  delete_partition (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  device_del (TYPE_2__*) ; 
 int /*<<< orphan*/  disk_part_iter_exit (struct disk_part_iter*) ; 
 int /*<<< orphan*/  disk_part_iter_init (struct disk_part_iter*,struct gendisk*,int) ; 
 struct hd_struct* disk_part_iter_next (struct disk_part_iter*) ; 
 TYPE_2__* disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  invalidate_partition (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_stat_set_all (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_gendisk (struct gendisk*) ; 

void del_gendisk(struct gendisk *disk)
{
	struct disk_part_iter piter;
	struct hd_struct *part;

	/* invalidate stuff */
	disk_part_iter_init(&piter, disk,
			     DISK_PITER_INCL_EMPTY | DISK_PITER_REVERSE);
	while ((part = disk_part_iter_next(&piter))) {
		invalidate_partition(disk, part->partno);
		delete_partition(disk, part->partno);
	}
	disk_part_iter_exit(&piter);

	invalidate_partition(disk, 0);
	set_capacity(disk, 0);
	disk->flags &= ~GENHD_FL_UP;
	unlink_gendisk(disk);
	part_stat_set_all(&disk->part0, 0);
	disk->part0.stamp = 0;

	kobject_put(disk->part0.holder_dir);
	kobject_put(disk->slave_dir);
	disk->driverfs_dev = NULL;
#ifndef CONFIG_SYSFS_DEPRECATED
	sysfs_remove_link(block_depr, dev_name(disk_to_dev(disk)));
#endif
	device_del(disk_to_dev(disk));
	blk_free_devt(disk_to_dev(disk)->devt);
}