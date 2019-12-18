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
struct gendisk {struct block_device_operations* fops; } ;
struct block_device_operations {int /*<<< orphan*/  (* revalidate_disk ) (struct gendisk*) ;int /*<<< orphan*/  (* media_changed ) (struct gendisk*) ;} ;
struct block_device {struct gendisk* bd_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_disk (struct block_device*,int) ; 
 int /*<<< orphan*/  stub1 (struct gendisk*) ; 
 int /*<<< orphan*/  stub2 (struct gendisk*) ; 

int check_disk_change(struct block_device *bdev)
{
	struct gendisk *disk = bdev->bd_disk;
	const struct block_device_operations *bdops = disk->fops;

	if (!bdops->media_changed)
		return 0;
	if (!bdops->media_changed(bdev->bd_disk))
		return 0;

	flush_disk(bdev, true);
	if (bdops->revalidate_disk)
		bdops->revalidate_disk(bdev->bd_disk);
	return 1;
}