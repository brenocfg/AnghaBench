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
struct scsi_device {int /*<<< orphan*/  device_busy; } ;
struct scsi_cmnd {int dummy; } ;
struct request_queue {struct scsi_device* queuedata; } ;
struct request {int errors; int /*<<< orphan*/  cmd_flags; struct scsi_cmnd* special; } ;

/* Variables and functions */
#define  BLKPREP_DEFER 129 
#define  BLKPREP_KILL 128 
 int DID_NO_CONNECT ; 
 int /*<<< orphan*/  REQ_DONTPREP ; 
 int /*<<< orphan*/  blk_plug_device (struct request_queue*) ; 
 int /*<<< orphan*/  scsi_put_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_release_buffers (struct scsi_cmnd*) ; 

int scsi_prep_return(struct request_queue *q, struct request *req, int ret)
{
	struct scsi_device *sdev = q->queuedata;

	switch (ret) {
	case BLKPREP_KILL:
		req->errors = DID_NO_CONNECT << 16;
		/* release the command and kill it */
		if (req->special) {
			struct scsi_cmnd *cmd = req->special;
			scsi_release_buffers(cmd);
			scsi_put_command(cmd);
			req->special = NULL;
		}
		break;
	case BLKPREP_DEFER:
		/*
		 * If we defer, the blk_peek_request() returns NULL, but the
		 * queue must be restarted, so we plug here if no returning
		 * command will automatically do that.
		 */
		if (sdev->device_busy == 0)
			blk_plug_device(q);
		break;
	default:
		req->cmd_flags |= REQ_DONTPREP;
	}

	return ret;
}