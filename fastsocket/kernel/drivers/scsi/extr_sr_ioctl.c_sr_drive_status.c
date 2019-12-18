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
struct scsi_sense_hdr {scalar_t__ sense_key; int asc; int ascq; } ;
struct scsi_cd {int /*<<< orphan*/  device; } ;
struct media_event_desc {scalar_t__ door_open; scalar_t__ media_present; } ;
struct cdrom_device_info {struct scsi_cd* handle; } ;

/* Variables and functions */
 int CDSL_CURRENT ; 
 int CDS_DISC_OK ; 
 int CDS_DRIVE_NOT_READY ; 
 int CDS_NO_DISC ; 
 int CDS_TRAY_OPEN ; 
 int EINVAL ; 
 scalar_t__ NOT_READY ; 
 int /*<<< orphan*/  cdrom_get_media_event (struct cdrom_device_info*,struct media_event_desc*) ; 
 scalar_t__ scsi_sense_valid (struct scsi_sense_hdr*) ; 
 scalar_t__ sr_test_unit_ready (int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 

int sr_drive_status(struct cdrom_device_info *cdi, int slot)
{
	struct scsi_cd *cd = cdi->handle;
	struct scsi_sense_hdr sshdr;
	struct media_event_desc med;

	if (CDSL_CURRENT != slot) {
		/* we have no changer support */
		return -EINVAL;
	}
	if (0 == sr_test_unit_ready(cd->device, &sshdr))
		return CDS_DISC_OK;

	/* SK/ASC/ASCQ of 2/4/1 means "unit is becoming ready" */
	if (scsi_sense_valid(&sshdr) && sshdr.sense_key == NOT_READY
			&& sshdr.asc == 0x04 && sshdr.ascq == 0x01)
		return CDS_DRIVE_NOT_READY;

	if (!cdrom_get_media_event(cdi, &med)) {
		if (med.media_present)
			return CDS_DISC_OK;
		else if (med.door_open)
			return CDS_TRAY_OPEN;
		else
			return CDS_NO_DISC;
	}

	/*
	 * SK/ASC/ASCQ of 2/4/2 means "initialization required"
	 * Using CD_TRAY_OPEN results in an START_STOP_UNIT to close
	 * the tray, which resolves the initialization requirement.
	 */
	if (scsi_sense_valid(&sshdr) && sshdr.sense_key == NOT_READY
			&& sshdr.asc == 0x04 && sshdr.ascq == 0x02)
		return CDS_TRAY_OPEN;

	/*
	 * 0x04 is format in progress .. but there must be a disc present!
	 */
	if (sshdr.sense_key == NOT_READY && sshdr.asc == 0x04)
		return CDS_DISC_OK;

	/*
	 * If not using Mt Fuji extended media tray reports,
	 * just return TRAY_OPEN since ATAPI doesn't provide
	 * any other way to detect this...
	 */
	if (scsi_sense_valid(&sshdr) &&
	    /* 0x3a is medium not present */
	    sshdr.asc == 0x3a)
		return CDS_NO_DISC;
	else
		return CDS_TRAY_OPEN;

	return CDS_DRIVE_NOT_READY;
}