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
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ pci_power_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ PCI_POWER_ERROR ; 
 int device_may_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_enable_wake (struct pci_dev*,scalar_t__,int) ; 
 int pci_set_power_state (struct pci_dev*,scalar_t__) ; 
 scalar_t__ pci_target_state (struct pci_dev*) ; 

int pci_prepare_to_sleep(struct pci_dev *dev)
{
	pci_power_t target_state = pci_target_state(dev);
	int error;

	if (target_state == PCI_POWER_ERROR)
		return -EIO;

	pci_enable_wake(dev, target_state, device_may_wakeup(&dev->dev));

	error = pci_set_power_state(dev, target_state);

	if (error)
		pci_enable_wake(dev, target_state, false);

	return error;
}