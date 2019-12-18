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
struct st_ccb {int srb_status; int scsi_status; struct scsi_cmnd* cmd; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;

/* Variables and functions */
 int COMMAND_COMPLETE ; 
 int DID_BUS_BUSY ; 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int DID_OK ; 
 int DRIVER_SENSE ; 
#define  SAM_STAT_BUSY 134 
#define  SAM_STAT_CHECK_CONDITION 133 
#define  SAM_STAT_GOOD 132 
 int SRB_SEE_SENSE ; 
#define  SRB_STATUS_BUSY 131 
#define  SRB_STATUS_ERROR 130 
#define  SRB_STATUS_INVALID_REQUEST 129 
#define  SRB_STATUS_SELECTION_TIMEOUT 128 
 int SRB_STATUS_SUCCESS ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void stex_scsi_done(struct st_ccb *ccb)
{
	struct scsi_cmnd *cmd = ccb->cmd;
	int result;

	if (ccb->srb_status == SRB_STATUS_SUCCESS || ccb->srb_status == 0) {
		result = ccb->scsi_status;
		switch (ccb->scsi_status) {
		case SAM_STAT_GOOD:
			result |= DID_OK << 16 | COMMAND_COMPLETE << 8;
			break;
		case SAM_STAT_CHECK_CONDITION:
			result |= DRIVER_SENSE << 24;
			break;
		case SAM_STAT_BUSY:
			result |= DID_BUS_BUSY << 16 | COMMAND_COMPLETE << 8;
			break;
		default:
			result |= DID_ERROR << 16 | COMMAND_COMPLETE << 8;
			break;
		}
	}
	else if (ccb->srb_status & SRB_SEE_SENSE)
		result = DRIVER_SENSE << 24 | SAM_STAT_CHECK_CONDITION;
	else switch (ccb->srb_status) {
		case SRB_STATUS_SELECTION_TIMEOUT:
			result = DID_NO_CONNECT << 16 | COMMAND_COMPLETE << 8;
			break;
		case SRB_STATUS_BUSY:
			result = DID_BUS_BUSY << 16 | COMMAND_COMPLETE << 8;
			break;
		case SRB_STATUS_INVALID_REQUEST:
		case SRB_STATUS_ERROR:
		default:
			result = DID_ERROR << 16 | COMMAND_COMPLETE << 8;
			break;
	}

	cmd->result = result;
	cmd->scsi_done(cmd);
}