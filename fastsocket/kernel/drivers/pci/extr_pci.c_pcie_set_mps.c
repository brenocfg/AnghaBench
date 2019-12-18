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
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_PAYLOAD ; 
 int ffs (int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int pcie_capability_clear_and_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rh_get_mpss (struct pci_dev*) ; 

int pcie_set_mps(struct pci_dev *dev, int mps)
{
	u16 v;

	if (mps < 128 || mps > 4096 || !is_power_of_2(mps))
		return -EINVAL;

	v = ffs(mps) - 8;
	if (v > rh_get_mpss(dev))
		return -EINVAL;
	v <<= 5;

	return pcie_capability_clear_and_set_word(dev, PCI_EXP_DEVCTL,
						  PCI_EXP_DEVCTL_PAYLOAD, v);
}