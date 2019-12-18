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
struct pci_dev {int /*<<< orphan*/  irq; scalar_t__ msix_enabled; scalar_t__ msi_enabled; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  eeh_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEH_MODE_IRQ_DISABLED ; 
 TYPE_1__* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_in_use (int /*<<< orphan*/ ) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 

__attribute__((used)) static void eeh_disable_irq(struct pci_dev *dev)
{
	struct device_node *dn = pci_device_to_OF_node(dev);

	/* Don't disable MSI and MSI-X interrupts. They are
	 * effectively disabled by the DMA Stopped state
	 * when an EEH error occurs.
	*/
	if (dev->msi_enabled || dev->msix_enabled)
		return;

	if (!irq_in_use(dev->irq))
		return;

	PCI_DN(dn)->eeh_mode |= EEH_MODE_IRQ_DISABLED;
	disable_irq_nosync(dev->irq);
}