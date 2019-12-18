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
struct TYPE_2__ {int /*<<< orphan*/  sem; } ;
struct pci_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int pci_af_flr (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_cfg_access_lock (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_cfg_access_unlock (struct pci_dev*) ; 
 int pci_dev_specific_reset (struct pci_dev*,int) ; 
 int pci_parent_bus_reset (struct pci_dev*,int) ; 
 int pci_pm_reset (struct pci_dev*,int) ; 
 int pcie_flr (struct pci_dev*,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pci_dev_reset(struct pci_dev *dev, int probe)
{
	int rc;

	might_sleep();

	if (!probe) {
		pci_cfg_access_lock(dev);
		/* block PM suspend, driver probe, etc. */
		down(&dev->dev.sem);
	}

	rc = pci_dev_specific_reset(dev, probe);
	if (rc != -ENOTTY)
		goto done;

	rc = pcie_flr(dev, probe);
	if (rc != -ENOTTY)
		goto done;

	rc = pci_af_flr(dev, probe);
	if (rc != -ENOTTY)
		goto done;

	rc = pci_pm_reset(dev, probe);
	if (rc != -ENOTTY)
		goto done;

	rc = pci_parent_bus_reset(dev, probe);
done:
	if (!probe) {
		up(&dev->dev.sem);
		pci_cfg_access_unlock(dev);
	}

	return rc;
}