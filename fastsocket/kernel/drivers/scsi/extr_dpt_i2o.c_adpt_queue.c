#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct scsi_cmnd {void (* scsi_done ) (struct scsi_cmnd*) ;scalar_t__* cmnd; scalar_t__* sense_buffer; int result; TYPE_2__* device; } ;
struct adpt_device {int state; TYPE_2__* pScsi_dev; } ;
struct TYPE_8__ {int state; } ;
typedef  TYPE_3__ adpt_hba ;
struct TYPE_7__ {struct adpt_device* hostdata; scalar_t__ lun; scalar_t__ id; scalar_t__ channel; TYPE_1__* host; } ;
struct TYPE_6__ {scalar_t__* hostdata; } ;

/* Variables and functions */
 int DID_NO_CONNECT ; 
 int DID_OK ; 
 int DPTI_DEV_RESET ; 
 int DPTI_STATE_RESET ; 
 int FAILED ; 
 scalar_t__ REQUEST_SENSE ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 struct adpt_device* adpt_find_device (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int adpt_scsi_to_i2o (TYPE_3__*,struct scsi_cmnd*,struct adpt_device*) ; 
 int /*<<< orphan*/  rmb () ; 
 void stub1 (struct scsi_cmnd*) ; 
 void stub2 (struct scsi_cmnd*) ; 

__attribute__((used)) static int adpt_queue(struct scsi_cmnd * cmd, void (*done) (struct scsi_cmnd *))
{
	adpt_hba* pHba = NULL;
	struct adpt_device* pDev = NULL;	/* dpt per device information */

	cmd->scsi_done = done;
	/*
	 * SCSI REQUEST_SENSE commands will be executed automatically by the 
	 * Host Adapter for any errors, so they should not be executed 
	 * explicitly unless the Sense Data is zero indicating that no error 
	 * occurred.
	 */

	if ((cmd->cmnd[0] == REQUEST_SENSE) && (cmd->sense_buffer[0] != 0)) {
		cmd->result = (DID_OK << 16);
		cmd->scsi_done(cmd);
		return 0;
	}

	pHba = (adpt_hba*)cmd->device->host->hostdata[0];
	if (!pHba) {
		return FAILED;
	}

	rmb();
	if((pHba->state) & DPTI_STATE_RESET)
		return SCSI_MLQUEUE_HOST_BUSY;

	// TODO if the cmd->device if offline then I may need to issue a bus rescan
	// followed by a get_lct to see if the device is there anymore
	if((pDev = (struct adpt_device*) (cmd->device->hostdata)) == NULL) {
		/*
		 * First command request for this device.  Set up a pointer
		 * to the device structure.  This should be a TEST_UNIT_READY
		 * command from scan_scsis_single.
		 */
		if ((pDev = adpt_find_device(pHba, (u32)cmd->device->channel, (u32)cmd->device->id, (u32)cmd->device->lun)) == NULL) {
			// TODO: if any luns are at this bus, scsi id then fake a TEST_UNIT_READY and INQUIRY response 
			// with type 7F (for all luns less than the max for this bus,id) so the lun scan will continue.
			cmd->result = (DID_NO_CONNECT << 16);
			cmd->scsi_done(cmd);
			return 0;
		}
		cmd->device->hostdata = pDev;
	}
	pDev->pScsi_dev = cmd->device;

	/*
	 * If we are being called from when the device is being reset, 
	 * delay processing of the command until later.
	 */
	if (pDev->state & DPTI_DEV_RESET ) {
		return FAILED;
	}
	return adpt_scsi_to_i2o(pHba, cmd, pDev);
}