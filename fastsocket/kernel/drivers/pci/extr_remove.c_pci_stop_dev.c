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
struct pci_dev {TYPE_1__* bus; scalar_t__ is_added; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ self; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_proc_detach_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_remove_sysfs_dev_files (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_aspm_exit_link_state (struct pci_dev*) ; 

__attribute__((used)) static void pci_stop_dev(struct pci_dev *dev)
{
	if (dev->is_added) {
		pci_proc_detach_device(dev);
		pci_remove_sysfs_dev_files(dev);
		device_unregister(&dev->dev);
		dev->is_added = 0;
	}

	if (dev->bus->self)
		pcie_aspm_exit_link_state(dev);
}