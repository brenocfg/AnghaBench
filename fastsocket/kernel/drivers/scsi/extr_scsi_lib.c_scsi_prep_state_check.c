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
struct scsi_device {int sdev_state; } ;
struct request {int cmd_flags; } ;

/* Variables and functions */
 int BLKPREP_DEFER ; 
 int BLKPREP_KILL ; 
 int BLKPREP_OK ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int REQ_PREEMPT ; 
#define  SDEV_BLOCK 133 
#define  SDEV_CREATED_BLOCK 132 
#define  SDEV_DEL 131 
#define  SDEV_OFFLINE 130 
#define  SDEV_QUIESCE 129 
 int SDEV_RUNNING ; 
#define  SDEV_TRANSPORT_OFFLINE 128 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*) ; 
 scalar_t__ unlikely (int) ; 

int scsi_prep_state_check(struct scsi_device *sdev, struct request *req)
{
	int ret = BLKPREP_OK;

	/*
	 * If the device is not in running state we will reject some
	 * or all commands.
	 */
	if (unlikely(sdev->sdev_state != SDEV_RUNNING)) {
		switch (sdev->sdev_state) {
		case SDEV_OFFLINE:
		case SDEV_TRANSPORT_OFFLINE:
			/*
			 * If the device is offline we refuse to process any
			 * commands.  The device must be brought online
			 * before trying any recovery commands.
			 */
			sdev_printk(KERN_ERR, sdev,
				    "rejecting I/O to offline device\n");
			ret = BLKPREP_KILL;
			break;
		case SDEV_DEL:
			/*
			 * If the device is fully deleted, we refuse to
			 * process any commands as well.
			 */
			sdev_printk(KERN_ERR, sdev,
				    "rejecting I/O to dead device\n");
			ret = BLKPREP_KILL;
			break;
		case SDEV_QUIESCE:
		case SDEV_BLOCK:
		case SDEV_CREATED_BLOCK:
			/*
			 * If the devices is blocked we defer normal commands.
			 */
			if (!(req->cmd_flags & REQ_PREEMPT))
				ret = BLKPREP_DEFER;
			break;
		default:
			/*
			 * For any other not fully online state we only allow
			 * special commands.  In particular any user initiated
			 * command is not allowed.
			 */
			if (!(req->cmd_flags & REQ_PREEMPT))
				ret = BLKPREP_KILL;
			break;
		}
	}
	return ret;
}