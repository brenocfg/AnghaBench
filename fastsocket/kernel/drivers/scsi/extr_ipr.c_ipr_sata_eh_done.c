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
struct TYPE_5__ {int /*<<< orphan*/  status; } ;
struct ipr_sata_port {TYPE_2__ ioasa; } ;
struct ipr_cmnd {TYPE_3__* hrrq; int /*<<< orphan*/  queue; struct ata_queued_cmd* qc; } ;
struct ata_queued_cmd {int /*<<< orphan*/  err_mask; TYPE_1__* ap; } ;
struct TYPE_6__ {int /*<<< orphan*/  hrrq_free_q; } ;
struct TYPE_4__ {struct ipr_sata_port* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ERR_OTHER ; 
 int /*<<< orphan*/  ATA_BUSY ; 
 int /*<<< orphan*/  ata_qc_complete (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipr_sata_eh_done(struct ipr_cmnd *ipr_cmd)
{
	struct ata_queued_cmd *qc = ipr_cmd->qc;
	struct ipr_sata_port *sata_port = qc->ap->private_data;

	qc->err_mask |= AC_ERR_OTHER;
	sata_port->ioasa.status |= ATA_BUSY;
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_free_q);
	ata_qc_complete(qc);
}