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
struct pd_unit {int capacity; int heads; int sectors; int cylinders; scalar_t__ alt_geom; } ;
struct hd_geometry {int heads; int sectors; int cylinders; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct TYPE_2__ {struct pd_unit* private_data; } ;

/* Variables and functions */
 int PD_LOG_HEADS ; 
 int PD_LOG_SECTS ; 

__attribute__((used)) static int pd_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct pd_unit *disk = bdev->bd_disk->private_data;

	if (disk->alt_geom) {
		geo->heads = PD_LOG_HEADS;
		geo->sectors = PD_LOG_SECTS;
		geo->cylinders = disk->capacity / (geo->heads * geo->sectors);
	} else {
		geo->heads = disk->heads;
		geo->sectors = disk->sectors;
		geo->cylinders = disk->cylinders;
	}

	return 0;
}