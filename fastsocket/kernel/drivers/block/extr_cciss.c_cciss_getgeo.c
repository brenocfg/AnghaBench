#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hd_geometry {scalar_t__ cylinders; int /*<<< orphan*/  sectors; int /*<<< orphan*/  heads; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
struct TYPE_3__ {scalar_t__ cylinders; int /*<<< orphan*/  sectors; int /*<<< orphan*/  heads; } ;
typedef  TYPE_1__ drive_info_struct ;

/* Variables and functions */
 int ENXIO ; 
 TYPE_1__* get_drv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cciss_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	drive_info_struct *drv = get_drv(bdev->bd_disk);

	if (!drv->cylinders)
		return -ENXIO;

	geo->heads = drv->heads;
	geo->sectors = drv->sectors;
	geo->cylinders = drv->cylinders;
	return 0;
}