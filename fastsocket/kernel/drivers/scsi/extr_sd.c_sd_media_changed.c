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
struct scsi_sense_hdr {int asc; } ;
struct scsi_disk {int media_present; int previous_state; struct scsi_device* device; } ;
struct scsi_device {int changed; int /*<<< orphan*/  removable; } ;
struct gendisk {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_LOG_HLQUEUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDEV_EVT_MEDIA_CHANGE ; 
 int /*<<< orphan*/  SD_MAX_RETRIES ; 
 int /*<<< orphan*/  SD_TIMEOUT ; 
 int /*<<< orphan*/  kfree (struct scsi_sense_hdr*) ; 
 struct scsi_sense_hdr* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_block_when_processing_errors (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_device_online (struct scsi_device*) ; 
 struct scsi_disk* scsi_disk (struct gendisk*) ; 
 scalar_t__ scsi_sense_valid (struct scsi_sense_hdr*) ; 
 int scsi_test_unit_ready (struct scsi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 
 int /*<<< orphan*/  sdev_evt_send_simple (struct scsi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_media_not_present (struct scsi_disk*) ; 

__attribute__((used)) static int sd_media_changed(struct gendisk *disk)
{
	struct scsi_disk *sdkp = scsi_disk(disk);
	struct scsi_device *sdp = sdkp->device;
	struct scsi_sense_hdr *sshdr = NULL;
	int retval;

	SCSI_LOG_HLQUEUE(3, sd_printk(KERN_INFO, sdkp, "sd_media_changed\n"));

	if (!sdp->removable)
		return 0;

	/*
	 * If the device is offline, don't send any commands - just pretend as
	 * if the command failed.  If the device ever comes back online, we
	 * can deal with it then.  It is only because of unrecoverable errors
	 * that we would ever take a device offline in the first place.
	 */
	if (!scsi_device_online(sdp)) {
		set_media_not_present(sdkp);
		retval = 1;
		goto out;
	}

	/*
	 * Using TEST_UNIT_READY enables differentiation between drive with
	 * no cartridge loaded - NOT READY, drive with changed cartridge -
	 * UNIT ATTENTION, or with same cartridge - GOOD STATUS.
	 *
	 * Drives that auto spin down. eg iomega jaz 1G, will be started
	 * by sd_spinup_disk() from sd_revalidate_disk(), which happens whenever
	 * sd_revalidate() is called.
	 */
	retval = -ENODEV;

	if (scsi_block_when_processing_errors(sdp)) {
		sshdr  = kzalloc(sizeof(*sshdr), GFP_KERNEL);
		retval = scsi_test_unit_ready(sdp, SD_TIMEOUT, SD_MAX_RETRIES,
					      sshdr);
	}

	/*
	 * Unable to test, unit probably not ready.   This usually
	 * means there is no disc in the drive.  Mark as changed,
	 * and we will figure it out later once the drive is
	 * available again.
	 */
	if (retval || (scsi_sense_valid(sshdr) &&
		       /* 0x3a is medium not present */
		       sshdr->asc == 0x3a)) {
		set_media_not_present(sdkp);
		retval = 1;
		goto out;
	}

	/*
	 * For removable scsi disk we have to recognise the presence
	 * of a disk in the drive. This is kept in the struct scsi_disk
	 * struct and tested at open !  Daniel Roche (dan@lectra.fr)
	 */
	sdkp->media_present = 1;

	retval = sdp->changed;
	sdp->changed = 0;
out:
	if (retval != sdkp->previous_state)
		sdev_evt_send_simple(sdp, SDEV_EVT_MEDIA_CHANGE, GFP_KERNEL);
	sdkp->previous_state = retval;
	kfree(sshdr);
	return retval;
}