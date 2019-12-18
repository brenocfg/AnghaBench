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
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_qla_host {TYPE_1__* reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_status; int /*<<< orphan*/ * mailbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_INTR_RISC ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_rmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qla4xxx_queue_mbox_cmd(struct scsi_qla_host *ha, uint32_t *mbx_cmd,
			    int in_count)
{
	int i;

	/* Load all mailbox registers, except mailbox 0. */
	for (i = 1; i < in_count; i++)
		writel(mbx_cmd[i], &ha->reg->mailbox[i]);

	/* Wakeup firmware  */
	writel(mbx_cmd[0], &ha->reg->mailbox[0]);
	readl(&ha->reg->mailbox[0]);
	writel(set_rmask(CSR_INTR_RISC), &ha->reg->ctrl_status);
	readl(&ha->reg->ctrl_status);
}