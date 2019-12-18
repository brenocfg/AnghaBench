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
struct pci_dev {int pme_support; int /*<<< orphan*/  dev; int /*<<< orphan*/  pm_cap; } ;
typedef  int pci_power_t ;

/* Variables and functions */
 int PCI_D0 ; 
#define  PCI_D1 131 
#define  PCI_D2 130 
 int PCI_D3hot ; 
#define  PCI_POWER_ERROR 129 
#define  PCI_UNKNOWN 128 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_no_d1d2 (struct pci_dev*) ; 
 int platform_pci_choose_state (struct pci_dev*) ; 
 scalar_t__ platform_pci_power_manageable (struct pci_dev*) ; 

pci_power_t pci_target_state(struct pci_dev *dev)
{
	pci_power_t target_state = PCI_D3hot;

	if (platform_pci_power_manageable(dev)) {
		/*
		 * Call the platform to choose the target state of the device
		 * and enable wake-up from this state if supported.
		 */
		pci_power_t state = platform_pci_choose_state(dev);

		switch (state) {
		case PCI_POWER_ERROR:
		case PCI_UNKNOWN:
			break;
		case PCI_D1:
		case PCI_D2:
			if (pci_no_d1d2(dev))
				break;
		default:
			target_state = state;
		}
	} else if (!dev->pm_cap) {
		target_state = PCI_D0;
	} else if (device_may_wakeup(&dev->dev)) {
		/*
		 * Find the deepest state from which the device can generate
		 * wake-up events, make it the target state and enable device
		 * to generate PME#.
		 */
		if (dev->pme_support) {
			while (target_state
			      && !(dev->pme_support & (1 << target_state)))
				target_state--;
		}
	}

	return target_state;
}