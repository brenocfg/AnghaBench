#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct flexcop_pci {int init_state; TYPE_1__* pdev; int /*<<< orphan*/  io_mem; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int FC_PCI_INIT ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct flexcop_pci*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_iounmap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_set_drvdata (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flexcop_pci_exit(struct flexcop_pci *fc_pci)
{
	if (fc_pci->init_state & FC_PCI_INIT) {
		free_irq(fc_pci->pdev->irq, fc_pci);
		pci_iounmap(fc_pci->pdev, fc_pci->io_mem);
		pci_set_drvdata(fc_pci->pdev, NULL);
		pci_release_regions(fc_pci->pdev);
		pci_disable_device(fc_pci->pdev);
	}
	fc_pci->init_state &= ~FC_PCI_INIT;
}