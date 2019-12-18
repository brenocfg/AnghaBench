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
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PCIE_BUS_PERFORMANCE ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_READRQ ; 
 int ffs (int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 scalar_t__ pcie_bus_config ; 
 int pcie_capability_clear_and_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pcie_get_mps (struct pci_dev*) ; 

int pcie_set_readrq(struct pci_dev *dev, int rq)
{
	u16 v;

	if (rq < 128 || rq > 4096 || !is_power_of_2(rq))
		return -EINVAL;

	/*
	 * If using the "performance" PCIe config, we clamp the
	 * read rq size to the max packet size to prevent the
	 * host bridge generating requests larger than we can
	 * cope with
	 */
	if (pcie_bus_config == PCIE_BUS_PERFORMANCE) {
		int mps = pcie_get_mps(dev);

		if (mps < 0)
			return mps;
		if (mps < rq)
			rq = mps;
	}

	v = (ffs(rq) - 8) << 12;

	return pcie_capability_clear_and_set_word(dev, PCI_EXP_DEVCTL,
						  PCI_EXP_DEVCTL_READRQ, v);
}