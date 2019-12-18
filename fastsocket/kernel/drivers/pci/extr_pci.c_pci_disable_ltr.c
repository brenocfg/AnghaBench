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
struct pci_dev {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_DEVCTL2 ; 
 int /*<<< orphan*/  PCI_EXP_LTR_EN ; 
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_ltr_supported (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_clear_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pci_disable_ltr(struct pci_dev *dev)
{
	/* Only primary function can enable/disable LTR */
	if (PCI_FUNC(dev->devfn) != 0)
		return;

	if (!pci_ltr_supported(dev))
		return;

	pcie_capability_clear_word(dev, PCI_EXP_DEVCTL2, PCI_EXP_LTR_EN);
}