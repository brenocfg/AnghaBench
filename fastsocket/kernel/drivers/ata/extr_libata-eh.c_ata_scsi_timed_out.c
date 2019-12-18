#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_3__* device; } ;
struct ata_queued_cmd {int /*<<< orphan*/  err_mask; int /*<<< orphan*/  flags; struct scsi_cmnd* scsicmd; } ;
struct TYPE_5__ {int /*<<< orphan*/  active_tag; } ;
struct ata_port {int /*<<< orphan*/  lock; TYPE_2__ link; TYPE_1__* ops; } ;
struct Scsi_Host {int dummy; } ;
typedef  enum blk_eh_timer_return { ____Placeholder_blk_eh_timer_return } blk_eh_timer_return ;
struct TYPE_6__ {struct Scsi_Host* host; } ;
struct TYPE_4__ {scalar_t__ error_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ATA_QCFLAG_EH_SCHEDULED ; 
 int BLK_EH_HANDLED ; 
 int BLK_EH_NOT_HANDLED ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ata_queued_cmd* ata_qc_from_tag (struct ata_port*,int /*<<< orphan*/ ) ; 
 struct ata_port* ata_shost_to_port (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

enum blk_eh_timer_return ata_scsi_timed_out(struct scsi_cmnd *cmd)
{
	struct Scsi_Host *host = cmd->device->host;
	struct ata_port *ap = ata_shost_to_port(host);
	unsigned long flags;
	struct ata_queued_cmd *qc;
	enum blk_eh_timer_return ret;

	DPRINTK("ENTER\n");

	if (ap->ops->error_handler) {
		ret = BLK_EH_NOT_HANDLED;
		goto out;
	}

	ret = BLK_EH_HANDLED;
	spin_lock_irqsave(ap->lock, flags);
	qc = ata_qc_from_tag(ap, ap->link.active_tag);
	if (qc) {
		WARN_ON(qc->scsicmd != cmd);
		qc->flags |= ATA_QCFLAG_EH_SCHEDULED;
		qc->err_mask |= AC_ERR_TIMEOUT;
		ret = BLK_EH_NOT_HANDLED;
	}
	spin_unlock_irqrestore(ap->lock, flags);

 out:
	DPRINTK("EXIT, ret=%d\n", ret);
	return ret;
}