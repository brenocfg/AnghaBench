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
struct gendisk {int /*<<< orphan*/ * private_data; } ;
struct device {int dummy; } ;
struct cdrom_device_info {TYPE_1__* handle; } ;
struct cdrom_info {struct cdrom_info* toc; struct gendisk* disk; TYPE_1__* drive; struct cdrom_device_info devinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; int /*<<< orphan*/ * driver_data; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_DBG_FUNC ; 
 int /*<<< orphan*/  blk_queue_prep_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdrom_info ; 
 int /*<<< orphan*/  ide_debug_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct cdrom_info*) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 struct cdrom_info* to_ide_drv (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_cdrom (struct cdrom_device_info*) ; 

__attribute__((used)) static void ide_cd_release(struct device *dev)
{
	struct cdrom_info *info = to_ide_drv(dev, cdrom_info);
	struct cdrom_device_info *devinfo = &info->devinfo;
	ide_drive_t *drive = info->drive;
	struct gendisk *g = info->disk;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	kfree(info->toc);
	if (devinfo->handle == drive)
		unregister_cdrom(devinfo);
	drive->driver_data = NULL;
	blk_queue_prep_rq(drive->queue, NULL);
	g->private_data = NULL;
	put_disk(g);
	kfree(info);
}