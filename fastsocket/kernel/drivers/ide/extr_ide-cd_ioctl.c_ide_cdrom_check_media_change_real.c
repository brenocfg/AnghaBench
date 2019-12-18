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
struct cdrom_device_info {TYPE_1__* handle; } ;
struct TYPE_3__ {int dev_flags; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int CDSL_CURRENT ; 
 int EINVAL ; 
 int IDE_DFLAG_MEDIA_CHANGED ; 
 int /*<<< orphan*/  cdrom_check_status (TYPE_1__*,int /*<<< orphan*/ *) ; 

int ide_cdrom_check_media_change_real(struct cdrom_device_info *cdi,
				       int slot_nr)
{
	ide_drive_t *drive = cdi->handle;
	int retval;

	if (slot_nr == CDSL_CURRENT) {
		(void) cdrom_check_status(drive, NULL);
		retval = (drive->dev_flags & IDE_DFLAG_MEDIA_CHANGED) ? 1 : 0;
		drive->dev_flags &= ~IDE_DFLAG_MEDIA_CHANGED;
		return retval;
	} else {
		return -EINVAL;
	}
}