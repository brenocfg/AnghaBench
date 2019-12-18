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
struct viodasd_device {int sectors; int tracks; int cylinders; } ;
struct hd_geometry {int sectors; int heads; int cylinders; } ;
struct gendisk {struct viodasd_device* private_data; } ;
struct block_device {struct gendisk* bd_disk; } ;

/* Variables and functions */
 int get_capacity (struct gendisk*) ; 

__attribute__((used)) static int viodasd_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct gendisk *disk = bdev->bd_disk;
	struct viodasd_device *d = disk->private_data;

	geo->sectors = d->sectors ? d->sectors : 32;
	geo->heads = d->tracks ? d->tracks  : 64;
	geo->cylinders = d->cylinders ? d->cylinders :
		get_capacity(disk) / (geo->sectors * geo->heads);

	return 0;
}