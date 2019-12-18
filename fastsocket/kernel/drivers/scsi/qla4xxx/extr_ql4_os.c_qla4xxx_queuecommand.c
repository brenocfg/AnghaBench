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
struct srb {int dummy; } ;
struct scsi_qla_host {TYPE_2__* host; int /*<<< orphan*/  srb_mempool; int /*<<< orphan*/  dpc_flags; int /*<<< orphan*/  flags; } ;
struct scsi_cmnd {int result; TYPE_1__* device; } ;
struct iscsi_cls_session {int dummy; } ;
struct ddb_entry {struct iscsi_cls_session* sess; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_3__ {struct ddb_entry* hostdata; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_EEH_BUSY ; 
 int /*<<< orphan*/  AF_LINK_UP ; 
 int /*<<< orphan*/  AF_LOOPBACK ; 
 int /*<<< orphan*/  AF_ONLINE ; 
 int /*<<< orphan*/  AF_PCI_CHANNEL_IO_PERM_FAILURE ; 
 int DID_IMM_RETRY ; 
 int DID_NO_CONNECT ; 
 int DID_REQUEUE ; 
 int /*<<< orphan*/  DPC_HA_NEED_QUIESCENT ; 
 int /*<<< orphan*/  DPC_HA_UNRECOVERABLE ; 
 int /*<<< orphan*/  DPC_RESET_ACTIVE ; 
 int /*<<< orphan*/  DPC_RESET_HA ; 
 int /*<<< orphan*/  DPC_RESET_HA_FW_CONTEXT ; 
 int /*<<< orphan*/  DPC_RESET_HA_INTR ; 
 int QLA_SUCCESS ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int iscsi_session_chkready (struct iscsi_cls_session*) ; 
 int /*<<< orphan*/  mempool_free (struct srb*,int /*<<< orphan*/ ) ; 
 struct srb* qla4xxx_get_new_srb (struct scsi_qla_host*,struct ddb_entry*,struct scsi_cmnd*,void (*) (struct scsi_cmnd*)) ; 
 int qla4xxx_send_command_to_isp (struct scsi_qla_host*,struct srb*) ; 
 int /*<<< orphan*/  qla4xxx_srb_free_dma (struct scsi_qla_host*,struct srb*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct scsi_qla_host* to_qla_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qla4xxx_queuecommand(struct scsi_cmnd *cmd,
				void (*done)(struct scsi_cmnd *))
{
	struct scsi_qla_host *ha = to_qla_host(cmd->device->host);
	struct ddb_entry *ddb_entry = cmd->device->hostdata;
	struct iscsi_cls_session *sess = ddb_entry->sess;
	struct srb *srb;
	int rval;

	if (test_bit(AF_EEH_BUSY, &ha->flags)) {
		if (test_bit(AF_PCI_CHANNEL_IO_PERM_FAILURE, &ha->flags))
			cmd->result = DID_NO_CONNECT << 16;
		else
			cmd->result = DID_REQUEUE << 16;
		goto qc_fail_command;
	}

	if (!sess) {
		cmd->result = DID_IMM_RETRY << 16;
		goto qc_fail_command;
	}

	rval = iscsi_session_chkready(sess);
	if (rval) {
		cmd->result = rval;
		goto qc_fail_command;
	}

	if (test_bit(DPC_RESET_HA_INTR, &ha->dpc_flags) ||
	    test_bit(DPC_RESET_ACTIVE, &ha->dpc_flags) ||
	    test_bit(DPC_RESET_HA, &ha->dpc_flags) ||
	    test_bit(DPC_HA_UNRECOVERABLE, &ha->dpc_flags) ||
	    test_bit(DPC_HA_NEED_QUIESCENT, &ha->dpc_flags) ||
	    !test_bit(AF_ONLINE, &ha->flags) ||
	    !test_bit(AF_LINK_UP, &ha->flags) ||
	    test_bit(AF_LOOPBACK, &ha->flags) ||
	    test_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags))
		goto qc_host_busy;

	spin_unlock_irq(ha->host->host_lock);

	srb = qla4xxx_get_new_srb(ha, ddb_entry, cmd, done);
	if (!srb)
		goto qc_host_busy_lock;

	rval = qla4xxx_send_command_to_isp(ha, srb);
	if (rval != QLA_SUCCESS)
		goto qc_host_busy_free_sp;

	spin_lock_irq(ha->host->host_lock);
	return 0;

qc_host_busy_free_sp:
	qla4xxx_srb_free_dma(ha, srb);
	mempool_free(srb, ha->srb_mempool);

qc_host_busy_lock:
	spin_lock_irq(ha->host->host_lock);

qc_host_busy:
	return SCSI_MLQUEUE_HOST_BUSY;

qc_fail_command:
	done(cmd);

	return 0;
}