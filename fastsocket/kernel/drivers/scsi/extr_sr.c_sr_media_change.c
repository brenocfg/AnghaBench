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
struct scsi_sense_hdr {int asc; } ;
struct scsi_cd {int previous_state; TYPE_1__* device; } ;
struct cdrom_device_info {struct scsi_cd* handle; } ;
struct TYPE_3__ {int changed; } ;

/* Variables and functions */
 int CDSL_CURRENT ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SDEV_EVT_MEDIA_CHANGE ; 
 int /*<<< orphan*/  get_sectorsize (struct scsi_cd*) ; 
 int /*<<< orphan*/  kfree (struct scsi_sense_hdr*) ; 
 struct scsi_sense_hdr* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_sense_valid (struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sdev_evt_send_simple (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sr_cd_check (struct cdrom_device_info*) ; 
 int sr_test_unit_ready (TYPE_1__*,struct scsi_sense_hdr*) ; 

__attribute__((used)) static int sr_media_change(struct cdrom_device_info *cdi, int slot)
{
	struct scsi_cd *cd = cdi->handle;
	int retval;
	struct scsi_sense_hdr *sshdr;

	if (CDSL_CURRENT != slot) {
		/* no changer support */
		return -EINVAL;
	}

	sshdr =  kzalloc(sizeof(*sshdr), GFP_KERNEL);
	retval = sr_test_unit_ready(cd->device, sshdr);
	if (retval || (scsi_sense_valid(sshdr) &&
		       /* 0x3a is medium not present */
		       sshdr->asc == 0x3a)) {
		/* Media not present or unable to test, unit probably not
		 * ready. This usually means there is no disc in the drive.
		 * Mark as changed, and we will figure it out later once
		 * the drive is available again.
		 */
		cd->device->changed = 1;
		/* This will force a flush, if called from check_disk_change */
		retval = 1;
		goto out;
	};

	retval = cd->device->changed;
	cd->device->changed = 0;
	/* If the disk changed, the capacity will now be different,
	 * so we force a re-read of this information */
	if (retval) {
		/* check multisession offset etc */
		sr_cd_check(cdi);
		get_sectorsize(cd);
	}

out:
	/* Notify userspace, that media has changed. */
	if (retval != cd->previous_state)
		sdev_evt_send_simple(cd->device, SDEV_EVT_MEDIA_CHANGE,
				     GFP_KERNEL);
	cd->previous_state = retval;
	kfree(sshdr);

	return retval;
}