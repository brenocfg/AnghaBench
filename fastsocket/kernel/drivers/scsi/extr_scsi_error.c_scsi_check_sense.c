#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_sense_hdr {int response_code; int additional_length; int sense_key; int asc; int ascq; } ;
struct scsi_device {int /*<<< orphan*/  retry_hwerror; int /*<<< orphan*/  allow_restart; int /*<<< orphan*/  expecting_cc_ua; TYPE_2__* scsi_dh_data; } ;
struct scsi_cmnd {int* sense_buffer; struct scsi_device* device; } ;
struct TYPE_4__ {TYPE_1__* scsi_dh; } ;
struct TYPE_3__ {int (* check_sense ) (struct scsi_device*,struct scsi_sense_hdr*) ;} ;

/* Variables and functions */
#define  ABORTED_COMMAND 140 
 int ADD_TO_MLQUEUE ; 
#define  BLANK_CHECK 139 
#define  COPY_ABORTED 138 
#define  DATA_PROTECT 137 
 int FAILED ; 
#define  HARDWARE_ERROR 136 
#define  ILLEGAL_REQUEST 135 
 int /*<<< orphan*/  KERN_WARNING ; 
#define  MEDIUM_ERROR 134 
#define  MISCOMPARE 133 
 int NEEDS_RETRY ; 
#define  NOT_READY 132 
#define  NO_SENSE 131 
#define  RECOVERED_ERROR 130 
 int SCSI_RETURN_NOT_HANDLED ; 
 int SUCCESS ; 
 int TARGET_ERROR ; 
#define  UNIT_ATTENTION 129 
#define  VOLUME_OVERFLOW 128 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*) ; 
 int /*<<< orphan*/  scsi_command_normalize_sense (struct scsi_cmnd*,struct scsi_sense_hdr*) ; 
 scalar_t__ scsi_sense_is_deferred (struct scsi_sense_hdr*) ; 
 int stub1 (struct scsi_device*,struct scsi_sense_hdr*) ; 

__attribute__((used)) static int scsi_check_sense(struct scsi_cmnd *scmd)
{
	struct scsi_device *sdev = scmd->device;
	struct scsi_sense_hdr sshdr;

	if (! scsi_command_normalize_sense(scmd, &sshdr))
		return FAILED;	/* no valid sense data */

	if (scsi_sense_is_deferred(&sshdr))
		return NEEDS_RETRY;

	if (sdev->scsi_dh_data && sdev->scsi_dh_data->scsi_dh &&
			sdev->scsi_dh_data->scsi_dh->check_sense) {
		int rc;

		rc = sdev->scsi_dh_data->scsi_dh->check_sense(sdev, &sshdr);
		if (rc != SCSI_RETURN_NOT_HANDLED)
			return rc;
		/* handler does not care. Drop down to default handling */
	}

	/*
	 * Previous logic looked for FILEMARK, EOM or ILI which are
	 * mainly associated with tapes and returned SUCCESS.
	 */
	if (sshdr.response_code == 0x70) {
		/* fixed format */
		if (scmd->sense_buffer[2] & 0xe0)
			return SUCCESS;
	} else {
		/*
		 * descriptor format: look for "stream commands sense data
		 * descriptor" (see SSC-3). Assume single sense data
		 * descriptor. Ignore ILI from SBC-2 READ LONG and WRITE LONG.
		 */
		if ((sshdr.additional_length > 3) &&
		    (scmd->sense_buffer[8] == 0x4) &&
		    (scmd->sense_buffer[11] & 0xe0))
			return SUCCESS;
	}

	switch (sshdr.sense_key) {
	case NO_SENSE:
		return SUCCESS;
	case RECOVERED_ERROR:
		return /* soft_error */ SUCCESS;

	case ABORTED_COMMAND:
		if (sshdr.asc == 0x10) /* DIF */
			return SUCCESS;

		return NEEDS_RETRY;
	case NOT_READY:
	case UNIT_ATTENTION:
		/*
		 * if we are expecting a cc/ua because of a bus reset that we
		 * performed, treat this just as a retry.  otherwise this is
		 * information that we should pass up to the upper-level driver
		 * so that we can deal with it there.
		 */
		if (scmd->device->expecting_cc_ua) {
			/*
			 * Because some device does not queue unit
			 * attentions correctly, we carefully check
			 * additional sense code and qualifier so as
			 * not to squash media change unit attention.
			 */
			if (sshdr.asc != 0x28 || sshdr.ascq != 0x00) {
				scmd->device->expecting_cc_ua = 0;
				return NEEDS_RETRY;
			}
		}
		/*
		 * if the device is in the process of becoming ready, we 
		 * should retry.
		 */
		if ((sshdr.asc == 0x04) && (sshdr.ascq == 0x01))
			return NEEDS_RETRY;
		/*
		 * if the device is not started, we need to wake
		 * the error handler to start the motor
		 */
		if (scmd->device->allow_restart &&
		    (sshdr.asc == 0x04) && (sshdr.ascq == 0x02))
			return FAILED;

		if (sshdr.asc == 0x3f && sshdr.ascq == 0x0e)
			scmd_printk(KERN_WARNING, scmd,
				    "Warning! Received an indication that the "
				    "LUN assignments on this target have "
				    "changed. The Linux SCSI layer does not "
				    "automatically remap LUN assignments.\n");
		else if (sshdr.asc == 0x3f)
			scmd_printk(KERN_WARNING, scmd,
				    "Warning! Received an indication that the "
				    "operating parameters on this target have "
				    "changed. The Linux SCSI layer does not "
				    "automatically adjust these parameters.\n");

		if (sshdr.asc == 0x38 && sshdr.ascq == 0x07)
			scmd_printk(KERN_WARNING, scmd,
				    "Warning! Received an indication that the "
				    "LUN reached a thin provisioning soft "
				    "threshold.\n");

		/*
		 * Pass the UA upwards for a determination in the completion
		 * functions.
		 */
		return SUCCESS;

		/* these are not supported */
	case COPY_ABORTED:
	case VOLUME_OVERFLOW:
	case MISCOMPARE:
	case BLANK_CHECK:
	case DATA_PROTECT:
		return TARGET_ERROR;

	case MEDIUM_ERROR:
		if (sshdr.asc == 0x11 || /* UNRECOVERED READ ERR */
		    sshdr.asc == 0x13 || /* AMNF DATA FIELD */
		    sshdr.asc == 0x14) { /* RECORD NOT FOUND */
			return TARGET_ERROR;
		}
		return NEEDS_RETRY;

	case HARDWARE_ERROR:
		if (scmd->device->retry_hwerror)
			return ADD_TO_MLQUEUE;
		else
			return TARGET_ERROR;

	case ILLEGAL_REQUEST:
		if (sshdr.asc == 0x20 || /* Invalid command operation code */
		    sshdr.asc == 0x21 || /* Logical block address out of range */
		    sshdr.asc == 0x24 || /* Invalid field in cdb */
		    sshdr.asc == 0x26) { /* Parameter value invalid */
			return TARGET_ERROR;
		}
		return SUCCESS;

	default:
		return SUCCESS;
	}
}