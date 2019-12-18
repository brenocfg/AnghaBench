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
struct request_sense {scalar_t__ sense_key; int asc; int ascq; } ;
struct media_event_desc {scalar_t__ door_open; scalar_t__ media_present; } ;
struct cdrom_device_info {int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int CDSL_CURRENT ; 
 int CDS_DISC_OK ; 
 int CDS_DRIVE_NOT_READY ; 
 int CDS_NO_DISC ; 
 int CDS_TRAY_OPEN ; 
 int EINVAL ; 
 scalar_t__ NOT_READY ; 
 scalar_t__ UNIT_ATTENTION ; 
 int cdrom_check_status (int /*<<< orphan*/ *,struct request_sense*) ; 
 int /*<<< orphan*/  cdrom_get_media_event (struct cdrom_device_info*,struct media_event_desc*) ; 

int ide_cdrom_drive_status(struct cdrom_device_info *cdi, int slot_nr)
{
	ide_drive_t *drive = cdi->handle;
	struct media_event_desc med;
	struct request_sense sense;
	int stat;

	if (slot_nr != CDSL_CURRENT)
		return -EINVAL;

	stat = cdrom_check_status(drive, &sense);
	if (!stat || sense.sense_key == UNIT_ATTENTION)
		return CDS_DISC_OK;

	if (!cdrom_get_media_event(cdi, &med)) {
		if (med.media_present)
			return CDS_DISC_OK;
		else if (med.door_open)
			return CDS_TRAY_OPEN;
		else
			return CDS_NO_DISC;
	}

	if (sense.sense_key == NOT_READY && sense.asc == 0x04
			&& sense.ascq == 0x04)
		return CDS_DISC_OK;

	/*
	 * If not using Mt Fuji extended media tray reports,
	 * just return TRAY_OPEN since ATAPI doesn't provide
	 * any other way to detect this...
	 */
	if (sense.sense_key == NOT_READY) {
		if (sense.asc == 0x3a && sense.ascq == 1)
			return CDS_NO_DISC;
		else
			return CDS_TRAY_OPEN;
	}
	return CDS_DRIVE_NOT_READY;
}