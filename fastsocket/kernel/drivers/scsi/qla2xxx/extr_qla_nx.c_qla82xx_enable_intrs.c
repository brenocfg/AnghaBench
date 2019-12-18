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
struct TYPE_2__ {int /*<<< orphan*/  tgt_mask_reg; } ;
struct qla_hw_data {int interrupts_on; int /*<<< orphan*/  hardware_lock; TYPE_1__ nx_legacy_intr; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla82xx_mbx_intr_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
qla82xx_enable_intrs(struct qla_hw_data *ha)
{
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);
	qla82xx_mbx_intr_enable(vha);
	spin_lock_irq(&ha->hardware_lock);
	qla82xx_wr_32(ha, ha->nx_legacy_intr.tgt_mask_reg, 0xfbff);
	spin_unlock_irq(&ha->hardware_lock);
	ha->interrupts_on = 1;
}