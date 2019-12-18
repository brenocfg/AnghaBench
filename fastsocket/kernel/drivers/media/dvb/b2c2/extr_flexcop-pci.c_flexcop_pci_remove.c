#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pci_dev {int dummy; } ;
struct flexcop_pci {int /*<<< orphan*/  fc_dev; int /*<<< orphan*/  irq_check_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flexcop_device_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flexcop_device_kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flexcop_pci_dma_exit (struct flexcop_pci*) ; 
 int /*<<< orphan*/  flexcop_pci_exit (struct flexcop_pci*) ; 
 scalar_t__ irq_chk_intv ; 
 struct flexcop_pci* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void flexcop_pci_remove(struct pci_dev *pdev)
{
	struct flexcop_pci *fc_pci = pci_get_drvdata(pdev);

	if (irq_chk_intv > 0)
		cancel_delayed_work(&fc_pci->irq_check_work);

	flexcop_pci_dma_exit(fc_pci);
	flexcop_device_exit(fc_pci->fc_dev);
	flexcop_pci_exit(fc_pci);
	flexcop_device_kfree(fc_pci->fc_dev);
}