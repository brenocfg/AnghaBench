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
struct pci_dev {int wakeup_prepared; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  pci_power_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  device_may_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_pme_active (struct pci_dev*,int) ; 
 scalar_t__ pci_pme_capable (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int platform_pci_sleep_wake (struct pci_dev*,int) ; 

int pci_enable_wake(struct pci_dev *dev, pci_power_t state, bool enable)
{
	int ret = 0;

	if (enable && !device_may_wakeup(&dev->dev))
		return -EINVAL;

	/* Don't do the same thing twice in a row for one device. */
	if (!!enable == !!dev->wakeup_prepared)
		return 0;

	/*
	 * According to "PCI System Architecture" 4th ed. by Tom Shanley & Don
	 * Anderson we should be doing PME# wake enable followed by ACPI wake
	 * enable.  To disable wake-up we call the platform first, for symmetry.
	 */

	if (enable) {
		int error;

		if (pci_pme_capable(dev, state))
			pci_pme_active(dev, true);
		else
			ret = 1;
		error = platform_pci_sleep_wake(dev, true);
		if (ret)
			ret = error;
		if (!ret)
			dev->wakeup_prepared = true;
	} else {
		platform_pci_sleep_wake(dev, false);
		pci_pme_active(dev, false);
		dev->wakeup_prepared = false;
	}

	return ret;
}