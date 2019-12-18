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
struct scsi_qla_host {TYPE_1__* pdev; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INTx_ENABLED ; 
 int /*<<< orphan*/  AF_IRQ_ATTACHED ; 
 int /*<<< orphan*/  AF_MSIX_ENABLED ; 
 int /*<<< orphan*/  AF_MSI_ENABLED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct scsi_qla_host*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 int /*<<< orphan*/  qla4_8xxx_disable_msix (struct scsi_qla_host*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qla4xxx_free_irqs(struct scsi_qla_host *ha)
{
	if (test_and_clear_bit(AF_IRQ_ATTACHED, &ha->flags)) {
		if (test_bit(AF_MSIX_ENABLED, &ha->flags)) {
			qla4_8xxx_disable_msix(ha);
		} else if (test_and_clear_bit(AF_MSI_ENABLED, &ha->flags)) {
			free_irq(ha->pdev->irq, ha);
			pci_disable_msi(ha->pdev);
		} else if (test_and_clear_bit(AF_INTx_ENABLED, &ha->flags)) {
			free_irq(ha->pdev->irq, ha);
		}
	}
}