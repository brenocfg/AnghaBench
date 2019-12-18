#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  sense_buffer; TYPE_1__* device; } ;
struct ipr_resource_entry {int needs_sync_complete; scalar_t__ in_erp; } ;
struct TYPE_7__ {int /*<<< orphan*/  ioasc; } ;
struct TYPE_8__ {TYPE_2__ hdr; } ;
struct TYPE_9__ {TYPE_3__ ioasa; } ;
struct ipr_cmnd {TYPE_5__* hrrq; int /*<<< orphan*/  queue; struct scsi_cmnd* scsi_cmd; int /*<<< orphan*/  sense_buffer; TYPE_4__ s; } ;
struct TYPE_10__ {int /*<<< orphan*/  hrrq_free_q; } ;
struct TYPE_6__ {struct ipr_resource_entry* hostdata; } ;

/* Variables and functions */
 int DID_ERROR ; 
 scalar_t__ IPR_IOASC_SENSE_KEY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_is_naca_model (struct ipr_resource_entry*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void ipr_erp_done(struct ipr_cmnd *ipr_cmd)
{
	struct scsi_cmnd *scsi_cmd = ipr_cmd->scsi_cmd;
	struct ipr_resource_entry *res = scsi_cmd->device->hostdata;
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

	if (IPR_IOASC_SENSE_KEY(ioasc) > 0) {
		scsi_cmd->result |= (DID_ERROR << 16);
		scmd_printk(KERN_ERR, scsi_cmd,
			    "Request Sense failed with IOASC: 0x%08X\n", ioasc);
	} else {
		memcpy(scsi_cmd->sense_buffer, ipr_cmd->sense_buffer,
		       SCSI_SENSE_BUFFERSIZE);
	}

	if (res) {
		if (!ipr_is_naca_model(res))
			res->needs_sync_complete = 1;
		res->in_erp = 0;
	}
	scsi_dma_unmap(ipr_cmd->scsi_cmd);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_free_q);
	scsi_cmd->scsi_done(scsi_cmd);
}