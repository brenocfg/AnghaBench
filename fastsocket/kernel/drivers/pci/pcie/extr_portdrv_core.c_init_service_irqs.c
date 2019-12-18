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
struct pci_dev {int irq; scalar_t__ pin; } ;

/* Variables and functions */
 int ENODEV ; 
 int PCIE_PORT_DEVICE_MAXSERVICES ; 
 int PCIE_PORT_SERVICE_HP ; 
 int PCIE_PORT_SERVICE_PME ; 
 size_t PCIE_PORT_SERVICE_VC_SHIFT ; 
 int /*<<< orphan*/  pci_enable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_port_enable_msix (struct pci_dev*,int*,int) ; 
 scalar_t__ pciehp_no_msi () ; 

__attribute__((used)) static int init_service_irqs(struct pci_dev *dev, int *irqs, int mask)
{
	int i, irq = -1;

	/*
	 * We have to use INTx if MSI cannot be used for PCIe PME or pciehp.
	 * RHEL6: pcie_pme_no_msi() not implemented, use 'false' instead
	 */
	if (((mask & PCIE_PORT_SERVICE_PME) && (false)) ||
	    ((mask & PCIE_PORT_SERVICE_HP) && pciehp_no_msi())) {
		if (dev->pin)
			irq = dev->irq;
		goto no_msi;
	}

	/* Try to use MSI-X if supported */
	if (!pcie_port_enable_msix(dev, irqs, mask))
		return 0;

	/* We're not going to use MSI-X, so try MSI and fall back to INTx */
	if (!pci_enable_msi(dev) || dev->pin)
		irq = dev->irq;

 no_msi:
	for (i = 0; i < PCIE_PORT_DEVICE_MAXSERVICES; i++)
		irqs[i] = irq;
	irqs[PCIE_PORT_SERVICE_VC_SHIFT] = -1;

	if (irq < 0)
		return -ENODEV;
	return 0;
}