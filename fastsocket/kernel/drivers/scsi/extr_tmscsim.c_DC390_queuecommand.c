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
struct scsi_device {scalar_t__ queue_depth; struct dc390_dcb* hostdata; TYPE_1__* host; } ;
struct scsi_cmnd {void (* scsi_done ) (struct scsi_cmnd*) ;char* host_scribble; scalar_t__ result; struct scsi_device* device; } ;
struct dc390_srb {int /*<<< orphan*/  TagNumber; scalar_t__ EndMessage; scalar_t__ ScsiPhase; scalar_t__ SGToBeXferLen; scalar_t__ SGBusAddr; scalar_t__ TotalXferredLen; scalar_t__ SRBState; scalar_t__ SRBFlag; scalar_t__ SRBStatus; scalar_t__ MsgCnt; scalar_t__ TargetStatus; scalar_t__ AdaptStatus; scalar_t__ SGIndex; struct scsi_cmnd* pcmd; struct dc390_dcb* pSRBDCB; struct dc390_srb* pNextSRB; } ;
struct dc390_dcb {scalar_t__ GoingSRBCnt; } ;
struct dc390_acb {int ACBFlag; struct dc390_srb* pFreeSRB; int /*<<< orphan*/  Cmds; scalar_t__ pActiveDCB; } ;
struct TYPE_2__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int RESET_DETECT ; 
 int RESET_DEV ; 
 int RESET_DONE ; 
 int SCSI_MLQUEUE_DEVICE_BUSY ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int /*<<< orphan*/  SCSI_NO_TAG ; 
 int /*<<< orphan*/  dc390_Free_insert (struct dc390_acb*,struct dc390_srb*) ; 
 int /*<<< orphan*/  dc390_Going_append (struct dc390_dcb*,struct dc390_srb*) ; 
 scalar_t__ dc390_StartSCSI (struct dc390_acb*,struct dc390_dcb*,struct dc390_srb*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DC390_queuecommand(struct scsi_cmnd *cmd,
		void (*done)(struct scsi_cmnd *))
{
	struct scsi_device *sdev = cmd->device;
	struct dc390_acb *acb = (struct dc390_acb *)sdev->host->hostdata;
	struct dc390_dcb *dcb = sdev->hostdata;
	struct dc390_srb *srb;

	if (sdev->queue_depth <= dcb->GoingSRBCnt)
		goto device_busy;
	if (acb->pActiveDCB)
		goto host_busy;
	if (acb->ACBFlag & (RESET_DETECT|RESET_DONE|RESET_DEV))
		goto host_busy;

	srb = acb->pFreeSRB;
	if (unlikely(srb == NULL))
		goto host_busy;

	cmd->scsi_done = done;
	cmd->result = 0;
	acb->Cmds++;

	acb->pFreeSRB = srb->pNextSRB;
	srb->pNextSRB = NULL;

	srb->pSRBDCB = dcb;
	srb->pcmd = cmd;
	cmd->host_scribble = (char *)srb;
    
	srb->SGIndex = 0;
	srb->AdaptStatus = 0;
	srb->TargetStatus = 0;
	srb->MsgCnt = 0;

	srb->SRBStatus = 0;
	srb->SRBFlag = 0;
	srb->SRBState = 0;
	srb->TotalXferredLen = 0;
	srb->SGBusAddr = 0;
	srb->SGToBeXferLen = 0;
	srb->ScsiPhase = 0;
	srb->EndMessage = 0;
	srb->TagNumber = SCSI_NO_TAG;

	if (dc390_StartSCSI(acb, dcb, srb)) {
		dc390_Free_insert(acb, srb);
		goto host_busy;
	}

	dc390_Going_append(dcb, srb);

	return 0;

 host_busy:
	return SCSI_MLQUEUE_HOST_BUSY;

 device_busy:
	return SCSI_MLQUEUE_DEVICE_BUSY;
}