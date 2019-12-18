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
struct scsi_device {int dummy; } ;
struct clariion_dh_data {int* buffer; int default_sp; int lun_state; int current_sp; int port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLARIION_NAME ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int SCSI_DH_DEV_TEMP_BUSY ; 
 int SCSI_DH_NOSYS ; 
 int SCSI_DH_OK ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int parse_sp_info_reply(struct scsi_device *sdev,
			       struct clariion_dh_data *csdev)
{
	int err = SCSI_DH_OK;

	/* check for in-progress ucode upgrade (NDU) */
	if (csdev->buffer[48] != 0) {
		sdev_printk(KERN_NOTICE, sdev, "%s: Detected in-progress "
			    "ucode upgrade NDU operation while finding "
			    "current active SP.", CLARIION_NAME);
		err = SCSI_DH_DEV_TEMP_BUSY;
		goto out;
	}
	if (csdev->buffer[4] > 2) {
		/* Invalid buffer format */
		sdev_printk(KERN_NOTICE, sdev,
			    "%s: invalid VPD page 0xC0 format\n",
			    CLARIION_NAME);
		err = SCSI_DH_NOSYS;
		goto out;
	}
	switch (csdev->buffer[28] & 0x0f) {
	case 6:
		sdev_printk(KERN_NOTICE, sdev,
			    "%s: ALUA failover mode detected\n",
			    CLARIION_NAME);
		break;
	case 4:
		/* Linux failover */
		break;
	default:
		sdev_printk(KERN_WARNING, sdev,
			    "%s: Invalid failover mode %d\n",
			    CLARIION_NAME, csdev->buffer[28] & 0x0f);
		err = SCSI_DH_NOSYS;
		goto out;
	}

	csdev->default_sp = csdev->buffer[5];
	csdev->lun_state = csdev->buffer[4];
	csdev->current_sp = csdev->buffer[8];
	csdev->port = csdev->buffer[7];

out:
	return err;
}