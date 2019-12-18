#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ide_disk_obj {int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  atapi_flags; int /*<<< orphan*/  queue; int /*<<< orphan*/  pc_delay; int /*<<< orphan*/  pc_callback; int /*<<< orphan*/ * id; struct ide_disk_obj* driver_data; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 size_t ATA_ID_PROD ; 
 int /*<<< orphan*/  IDEFLOPPY_PC_DELAY ; 
 int /*<<< orphan*/  IDE_AFLAG_CLIK_DRIVE ; 
 int /*<<< orphan*/  IDE_AFLAG_ZIP_DRIVE ; 
 int /*<<< orphan*/  IDE_DFLAG_ATTACH ; 
 int /*<<< orphan*/  IDE_DFLAG_DOORLOCKING ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ide_floppy_callback ; 
 int /*<<< orphan*/  ide_floppy_get_capacity (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_proc_register_driver (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void ide_floppy_setup(ide_drive_t *drive)
{
	struct ide_disk_obj *floppy = drive->driver_data;
	u16 *id = drive->id;

	drive->pc_callback	 = ide_floppy_callback;

	/*
	 * We used to check revisions here. At this point however I'm giving up.
	 * Just assume they are all broken, its easier.
	 *
	 * The actual reason for the workarounds was likely a driver bug after
	 * all rather than a firmware bug, and the workaround below used to hide
	 * it. It should be fixed as of version 1.9, but to be on the safe side
	 * we'll leave the limitation below for the 2.2.x tree.
	 */
	if (!strncmp((char *)&id[ATA_ID_PROD], "IOMEGA ZIP 100 ATAPI", 20)) {
		drive->atapi_flags |= IDE_AFLAG_ZIP_DRIVE;
		/* This value will be visible in the /proc/ide/hdx/settings */
		drive->pc_delay = IDEFLOPPY_PC_DELAY;
		blk_queue_max_hw_sectors(drive->queue, 64);
	}

	/*
	 * Guess what? The IOMEGA Clik! drive also needs the above fix. It makes
	 * nasty clicking noises without it, so please don't remove this.
	 */
	if (strncmp((char *)&id[ATA_ID_PROD], "IOMEGA Clik!", 11) == 0) {
		blk_queue_max_hw_sectors(drive->queue, 64);
		drive->atapi_flags |= IDE_AFLAG_CLIK_DRIVE;
		/* IOMEGA Clik! drives do not support lock/unlock commands */
		drive->dev_flags &= ~IDE_DFLAG_DOORLOCKING;
	}

	(void) ide_floppy_get_capacity(drive);

	ide_proc_register_driver(drive, floppy->driver);

	drive->dev_flags |= IDE_DFLAG_ATTACH;
}