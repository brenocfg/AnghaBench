#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct scsi_cmnd {TYPE_2__* device; } ;
struct pmcraid_resource_entry {int /*<<< orphan*/  cfg_entry; } ;
struct pmcraid_ioarcb {int ioarcb_bus_addr; scalar_t__ data_transfer_length; scalar_t__ ioadl_length; scalar_t__ ioadl_bus_addr; int /*<<< orphan*/ * cdb; int /*<<< orphan*/  request_type; int /*<<< orphan*/  request_flags0; } ;
struct pmcraid_cmd {TYPE_1__* ioa_cb; struct scsi_cmnd* scsi_cmd; } ;
struct TYPE_4__ {struct pmcraid_resource_entry* hostdata; } ;
struct TYPE_3__ {struct pmcraid_ioarcb ioarcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCRAID_CANCEL_ALL_REQUESTS ; 
 int /*<<< orphan*/  PMCRAID_MAX_CDB_LEN ; 
 int /*<<< orphan*/  PMCRAID_REQUEST_SENSE_TIMEOUT ; 
 int /*<<< orphan*/  PMCRAID_SYNC_COMPLETE_AFTER_CANCEL ; 
 int /*<<< orphan*/  REQ_TYPE_IOACMD ; 
 scalar_t__ RES_IS_GSCSI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNC_OVERRIDE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void pmcraid_erp_done (struct pmcraid_cmd*) ; 
 void pmcraid_request_sense (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  pmcraid_send_cmd (struct pmcraid_cmd*,void (*) (struct pmcraid_cmd*),int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_timeout_handler ; 

__attribute__((used)) static void pmcraid_cancel_all(struct pmcraid_cmd *cmd, u32 sense)
{
	struct scsi_cmnd *scsi_cmd = cmd->scsi_cmd;
	struct pmcraid_ioarcb *ioarcb = &cmd->ioa_cb->ioarcb;
	struct pmcraid_resource_entry *res = scsi_cmd->device->hostdata;
	void (*cmd_done) (struct pmcraid_cmd *) = sense ? pmcraid_erp_done
							: pmcraid_request_sense;

	memset(ioarcb->cdb, 0, PMCRAID_MAX_CDB_LEN);
	ioarcb->request_flags0 = SYNC_OVERRIDE;
	ioarcb->request_type = REQ_TYPE_IOACMD;
	ioarcb->cdb[0] = PMCRAID_CANCEL_ALL_REQUESTS;

	if (RES_IS_GSCSI(res->cfg_entry))
		ioarcb->cdb[1] = PMCRAID_SYNC_COMPLETE_AFTER_CANCEL;

	ioarcb->ioadl_bus_addr = 0;
	ioarcb->ioadl_length = 0;
	ioarcb->data_transfer_length = 0;
	ioarcb->ioarcb_bus_addr &= (~0x1FULL);

	/* writing to IOARRIN must be protected by host_lock, as mid-layer
	 * schedule queuecommand while we are doing this
	 */
	pmcraid_send_cmd(cmd, cmd_done,
			 PMCRAID_REQUEST_SENSE_TIMEOUT,
			 pmcraid_timeout_handler);
}