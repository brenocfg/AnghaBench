#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_sense {int dummy; } ;
struct cdrom_device_info {int mask; } ;
struct cdrom_info {struct cdrom_device_info devinfo; } ;
struct TYPE_4__ {int atapi_flags; struct cdrom_info* driver_data; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int BLK_MAX_CDB ; 
 int CDC_CLOSE_TRAY ; 
 int EDRIVE_CANT_DO_THIS ; 
 unsigned char GPCMD_START_STOP_UNIT ; 
 int IDE_AFLAG_DOOR_LOCKED ; 
 int IDE_AFLAG_NO_EJECT ; 
 int ide_cd_queue_pc (TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct request_sense*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
int cdrom_eject(ide_drive_t *drive, int ejectflag,
		struct request_sense *sense)
{
	struct cdrom_info *cd = drive->driver_data;
	struct cdrom_device_info *cdi = &cd->devinfo;
	char loej = 0x02;
	unsigned char cmd[BLK_MAX_CDB];

	if ((drive->atapi_flags & IDE_AFLAG_NO_EJECT) && !ejectflag)
		return -EDRIVE_CANT_DO_THIS;

	/* reload fails on some drives, if the tray is locked */
	if ((drive->atapi_flags & IDE_AFLAG_DOOR_LOCKED) && ejectflag)
		return 0;

	/* only tell drive to close tray if open, if it can do that */
	if (ejectflag && (cdi->mask & CDC_CLOSE_TRAY))
		loej = 0;

	memset(cmd, 0, BLK_MAX_CDB);

	cmd[0] = GPCMD_START_STOP_UNIT;
	cmd[4] = loej | (ejectflag != 0);

	return ide_cd_queue_pc(drive, cmd, 0, NULL, NULL, sense, 0, 0);
}