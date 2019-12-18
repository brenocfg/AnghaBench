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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct scsi_qla_host {int /*<<< orphan*/  hardware_lock; TYPE_2__* isp_ops; } ;
struct queue_entry {int dummy; } ;
struct TYPE_3__ {int entryCount; int /*<<< orphan*/  entryType; } ;
struct qla4_marker_entry {int /*<<< orphan*/  lun; void* modifier; void* target; TYPE_1__ hdr; } ;
struct ddb_entry {int /*<<< orphan*/  fw_ddb_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* queue_iocb ) (struct scsi_qla_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ET_MARKER ; 
 int QLA_ERROR ; 
 scalar_t__ QLA_SUCCESS ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_to_scsilun (int,int /*<<< orphan*/ *) ; 
 scalar_t__ qla4xxx_get_req_pkt (struct scsi_qla_host*,struct queue_entry**) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  wmb () ; 

int qla4xxx_send_marker_iocb(struct scsi_qla_host *ha,
	struct ddb_entry *ddb_entry, int lun, uint16_t mrkr_mod)
{
	struct qla4_marker_entry *marker_entry;
	unsigned long flags = 0;
	uint8_t status = QLA_SUCCESS;

	/* Acquire hardware specific lock */
	spin_lock_irqsave(&ha->hardware_lock, flags);

	/* Get pointer to the queue entry for the marker */
	if (qla4xxx_get_req_pkt(ha, (struct queue_entry **) &marker_entry) !=
	    QLA_SUCCESS) {
		status = QLA_ERROR;
		goto exit_send_marker;
	}

	/* Put the marker in the request queue */
	marker_entry->hdr.entryType = ET_MARKER;
	marker_entry->hdr.entryCount = 1;
	marker_entry->target = cpu_to_le16(ddb_entry->fw_ddb_index);
	marker_entry->modifier = cpu_to_le16(mrkr_mod);
	int_to_scsilun(lun, &marker_entry->lun);
	wmb();

	/* Tell ISP it's got a new I/O request */
	ha->isp_ops->queue_iocb(ha);

exit_send_marker:
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	return status;
}