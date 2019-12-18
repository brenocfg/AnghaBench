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
struct cdrom_device_info {int capacity; int /*<<< orphan*/  disk; int /*<<< orphan*/  mask; int /*<<< orphan*/  name; TYPE_1__* handle; int /*<<< orphan*/  speed; int /*<<< orphan*/ * ops; } ;
struct cdrom_info {int /*<<< orphan*/  disk; int /*<<< orphan*/  current_speed; struct cdrom_device_info devinfo; } ;
struct TYPE_3__ {int atapi_flags; int /*<<< orphan*/  name; struct cdrom_info* driver_data; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_SELECT_SPEED ; 
 int IDE_AFLAG_NO_SPEED_SELECT ; 
 int /*<<< orphan*/  IDE_DBG_PROBE ; 
 int /*<<< orphan*/  ide_cdrom_dops ; 
 int /*<<< orphan*/  ide_debug_log (int /*<<< orphan*/ ,char*,int) ; 
 int register_cdrom (struct cdrom_device_info*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ide_cdrom_register(ide_drive_t *drive, int nslots)
{
	struct cdrom_info *info = drive->driver_data;
	struct cdrom_device_info *devinfo = &info->devinfo;

	ide_debug_log(IDE_DBG_PROBE, "nslots: %d", nslots);

	devinfo->ops = &ide_cdrom_dops;
	devinfo->speed = info->current_speed;
	devinfo->capacity = nslots;
	devinfo->handle = drive;
	strcpy(devinfo->name, drive->name);

	if (drive->atapi_flags & IDE_AFLAG_NO_SPEED_SELECT)
		devinfo->mask |= CDC_SELECT_SPEED;

	devinfo->disk = info->disk;
	return register_cdrom(devinfo);
}