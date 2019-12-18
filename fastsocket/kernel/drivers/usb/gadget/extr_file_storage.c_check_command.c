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
struct lun {scalar_t__ sense_data; scalar_t__ unit_attention_data; scalar_t__ info_valid; scalar_t__ sense_data_info; } ;
struct fsg_dev {int* cmnd; int cmnd_size; scalar_t__ data_dir; int data_size; int data_size_from_cmnd; int phase_error; int residue; int usb_amount_left; int lun; int nluns; scalar_t__ bad_lun_okay; struct lun* curlun; struct lun* luns; } ;
typedef  enum data_direction { ____Placeholder_data_direction } data_direction ;
struct TYPE_2__ {scalar_t__ protocol_type; } ;

/* Variables and functions */
 int DATA_DIR_NONE ; 
 scalar_t__ DATA_DIR_UNKNOWN ; 
 int /*<<< orphan*/  DBG (struct fsg_dev*,char*,...) ; 
 int EINVAL ; 
 int SC_INQUIRY ; 
 int SC_REQUEST_SENSE ; 
 scalar_t__ SS_INVALID_FIELD_IN_CDB ; 
 scalar_t__ SS_MEDIUM_NOT_PRESENT ; 
 scalar_t__ SS_NO_SENSE ; 
 scalar_t__ USB_SC_RBC ; 
 int /*<<< orphan*/  VDBG (struct fsg_dev*,char*,char const*,int,char const,int,int,char*) ; 
 int /*<<< orphan*/  backing_file_is_open (struct lun*) ; 
 TYPE_1__ mod_data ; 
 scalar_t__ protocol_is_scsi () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const,int) ; 
 scalar_t__ transport_is_bbb () ; 

__attribute__((used)) static int check_command(struct fsg_dev *fsg, int cmnd_size,
		enum data_direction data_dir, unsigned int mask,
		int needs_medium, const char *name)
{
	int			i;
	int			lun = fsg->cmnd[1] >> 5;
	static const char	dirletter[4] = {'u', 'o', 'i', 'n'};
	char			hdlen[20];
	struct lun		*curlun;

	/* Adjust the expected cmnd_size for protocol encapsulation padding.
	 * Transparent SCSI doesn't pad. */
	if (protocol_is_scsi())
		;

	/* There's some disagreement as to whether RBC pads commands or not.
	 * We'll play it safe and accept either form. */
	else if (mod_data.protocol_type == USB_SC_RBC) {
		if (fsg->cmnd_size == 12)
			cmnd_size = 12;

	/* All the other protocols pad to 12 bytes */
	} else
		cmnd_size = 12;

	hdlen[0] = 0;
	if (fsg->data_dir != DATA_DIR_UNKNOWN)
		sprintf(hdlen, ", H%c=%u", dirletter[(int) fsg->data_dir],
				fsg->data_size);
	VDBG(fsg, "SCSI command: %s;  Dc=%d, D%c=%u;  Hc=%d%s\n",
			name, cmnd_size, dirletter[(int) data_dir],
			fsg->data_size_from_cmnd, fsg->cmnd_size, hdlen);

	/* We can't reply at all until we know the correct data direction
	 * and size. */
	if (fsg->data_size_from_cmnd == 0)
		data_dir = DATA_DIR_NONE;
	if (fsg->data_dir == DATA_DIR_UNKNOWN) {	// CB or CBI
		fsg->data_dir = data_dir;
		fsg->data_size = fsg->data_size_from_cmnd;

	} else {					// Bulk-only
		if (fsg->data_size < fsg->data_size_from_cmnd) {

			/* Host data size < Device data size is a phase error.
			 * Carry out the command, but only transfer as much
			 * as we are allowed. */
			fsg->data_size_from_cmnd = fsg->data_size;
			fsg->phase_error = 1;
		}
	}
	fsg->residue = fsg->usb_amount_left = fsg->data_size;

	/* Conflicting data directions is a phase error */
	if (fsg->data_dir != data_dir && fsg->data_size_from_cmnd > 0) {
		fsg->phase_error = 1;
		return -EINVAL;
	}

	/* Verify the length of the command itself */
	if (cmnd_size != fsg->cmnd_size) {

		/* Special case workaround: There are plenty of buggy SCSI
		 * implementations. Many have issues with cbw->Length
		 * field passing a wrong command size. For those cases we
		 * always try to work around the problem by using the length
		 * sent by the host side provided it is at least as large
		 * as the correct command length.
		 * Examples of such cases would be MS-Windows, which issues
		 * REQUEST SENSE with cbw->Length == 12 where it should
		 * be 6, and xbox360 issuing INQUIRY, TEST UNIT READY and
		 * REQUEST SENSE with cbw->Length == 10 where it should
		 * be 6 as well.
		 */
		if (cmnd_size <= fsg->cmnd_size) {
			DBG(fsg, "%s is buggy! Expected length %d "
					"but we got %d\n", name,
					cmnd_size, fsg->cmnd_size);
			cmnd_size = fsg->cmnd_size;
		} else {
			fsg->phase_error = 1;
			return -EINVAL;
		}
	}

	/* Check that the LUN values are consistent */
	if (transport_is_bbb()) {
		if (fsg->lun != lun)
			DBG(fsg, "using LUN %d from CBW, "
					"not LUN %d from CDB\n",
					fsg->lun, lun);
	} else
		fsg->lun = lun;		// Use LUN from the command

	/* Check the LUN */
	if (fsg->lun >= 0 && fsg->lun < fsg->nluns) {
		fsg->curlun = curlun = &fsg->luns[fsg->lun];
		if (fsg->cmnd[0] != SC_REQUEST_SENSE) {
			curlun->sense_data = SS_NO_SENSE;
			curlun->sense_data_info = 0;
			curlun->info_valid = 0;
		}
	} else {
		fsg->curlun = curlun = NULL;
		fsg->bad_lun_okay = 0;

		/* INQUIRY and REQUEST SENSE commands are explicitly allowed
		 * to use unsupported LUNs; all others may not. */
		if (fsg->cmnd[0] != SC_INQUIRY &&
				fsg->cmnd[0] != SC_REQUEST_SENSE) {
			DBG(fsg, "unsupported LUN %d\n", fsg->lun);
			return -EINVAL;
		}
	}

	/* If a unit attention condition exists, only INQUIRY and
	 * REQUEST SENSE commands are allowed; anything else must fail. */
	if (curlun && curlun->unit_attention_data != SS_NO_SENSE &&
			fsg->cmnd[0] != SC_INQUIRY &&
			fsg->cmnd[0] != SC_REQUEST_SENSE) {
		curlun->sense_data = curlun->unit_attention_data;
		curlun->unit_attention_data = SS_NO_SENSE;
		return -EINVAL;
	}

	/* Check that only command bytes listed in the mask are non-zero */
	fsg->cmnd[1] &= 0x1f;			// Mask away the LUN
	for (i = 1; i < cmnd_size; ++i) {
		if (fsg->cmnd[i] && !(mask & (1 << i))) {
			if (curlun)
				curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
			return -EINVAL;
		}
	}

	/* If the medium isn't mounted and the command needs to access
	 * it, return an error. */
	if (curlun && !backing_file_is_open(curlun) && needs_medium) {
		curlun->sense_data = SS_MEDIUM_NOT_PRESENT;
		return -EINVAL;
	}

	return 0;
}