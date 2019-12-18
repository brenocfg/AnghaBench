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
struct pci_dev {TYPE_1__* bus; int /*<<< orphan*/  devfn; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL2 ; 
 int /*<<< orphan*/  PCI_EXP_LTR_EN ; 
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_ltr_supported (struct pci_dev*) ; 
 int pcie_capability_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pci_enable_ltr(struct pci_dev *dev)
{
	int ret;

	/* Only primary function can enable/disable LTR */
	if (PCI_FUNC(dev->devfn) != 0)
		return -EINVAL;

	if (!pci_ltr_supported(dev))
		return -ENOTSUPP;

	/* Enable upstream ports first */
	if (dev->bus->self) {
		ret = pci_enable_ltr(dev->bus->self);
		if (ret)
			return ret;
	}

	return pcie_capability_set_word(dev, PCI_EXP_DEVCTL2, PCI_EXP_LTR_EN);
}