#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  phase; } ;
struct scsi_cmnd {int result; void (* scsi_done ) (struct scsi_cmnd*) ;TYPE_4__ SCp; TYPE_2__* device; } ;
struct TYPE_11__ {scalar_t__ working_srl; } ;
struct TYPE_13__ {int /*<<< orphan*/ * state; struct scsi_cmnd** srb; TYPE_3__ tw_compat_info; int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {scalar_t__ lun; TYPE_1__* host; } ;
struct TYPE_9__ {scalar_t__ hostdata; } ;
typedef  TYPE_5__ TW_Device_Extension ;

/* Variables and functions */
 int DID_BAD_TARGET ; 
 int DID_ERROR ; 
#define  SCSI_MLQUEUE_HOST_BUSY 128 
 scalar_t__ TW_FW_SRL_LUNS_SUPPORTED ; 
 int /*<<< orphan*/  TW_IN_RESET ; 
 int /*<<< orphan*/  TW_PHASE_INITIAL ; 
 int /*<<< orphan*/  TW_S_COMPLETED ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twa_free_request_id (TYPE_5__*,int) ; 
 int /*<<< orphan*/  twa_get_request_id (TYPE_5__*,int*) ; 
 int twa_scsiop_execute_scsi (TYPE_5__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int twa_scsi_queue(struct scsi_cmnd *SCpnt, void (*done)(struct scsi_cmnd *))
{
	int request_id, retval;
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)SCpnt->device->host->hostdata;

	/* If we are resetting due to timed out ioctl, report as busy */
	if (test_bit(TW_IN_RESET, &tw_dev->flags)) {
		retval = SCSI_MLQUEUE_HOST_BUSY;
		goto out;
	}

	/* Check if this FW supports luns */
	if ((SCpnt->device->lun != 0) && (tw_dev->tw_compat_info.working_srl < TW_FW_SRL_LUNS_SUPPORTED)) {
		SCpnt->result = (DID_BAD_TARGET << 16);
		done(SCpnt);
		retval = 0;
		goto out;
	}

	/* Save done function into scsi_cmnd struct */
	SCpnt->scsi_done = done;
		
	/* Get a free request id */
	twa_get_request_id(tw_dev, &request_id);

	/* Save the scsi command for use by the ISR */
	tw_dev->srb[request_id] = SCpnt;

	/* Initialize phase to zero */
	SCpnt->SCp.phase = TW_PHASE_INITIAL;

	retval = twa_scsiop_execute_scsi(tw_dev, request_id, NULL, 0, NULL);
	switch (retval) {
	case SCSI_MLQUEUE_HOST_BUSY:
		twa_free_request_id(tw_dev, request_id);
		break;
	case 1:
		tw_dev->state[request_id] = TW_S_COMPLETED;
		twa_free_request_id(tw_dev, request_id);
		SCpnt->result = (DID_ERROR << 16);
		done(SCpnt);
		retval = 0;
	}
out:
	return retval;
}