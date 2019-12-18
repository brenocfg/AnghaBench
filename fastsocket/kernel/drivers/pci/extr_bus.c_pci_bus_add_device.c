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
struct pci_dev {int is_added; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_create_sysfs_dev_files (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_proc_attach_device (struct pci_dev*) ; 

int pci_bus_add_device(struct pci_dev *dev)
{
	int retval;
	retval = device_add(&dev->dev);
	if (retval)
		return retval;

	dev->is_added = 1;
	pci_proc_attach_device(dev);
	pci_create_sysfs_dev_files(dev);
	return 0;
}