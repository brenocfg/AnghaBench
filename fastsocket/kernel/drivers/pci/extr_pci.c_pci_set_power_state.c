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
struct pci_dev {int dev_flags; } ;
typedef  scalar_t__ pci_power_t ;

/* Variables and functions */
 scalar_t__ PCI_D0 ; 
 scalar_t__ PCI_D1 ; 
 scalar_t__ PCI_D2 ; 
 scalar_t__ PCI_D3hot ; 
 int PCI_DEV_FLAGS_NO_D3 ; 
 int /*<<< orphan*/  __pci_complete_power_transition (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  __pci_start_power_transition (struct pci_dev*,scalar_t__) ; 
 scalar_t__ pci_no_d1d2 (struct pci_dev*) ; 
 int pci_raw_set_power_state (struct pci_dev*,scalar_t__) ; 

int pci_set_power_state(struct pci_dev *dev, pci_power_t state)
{
	int error;

	/* bound the state we're entering */
	if (state > PCI_D3hot)
		state = PCI_D3hot;
	else if (state < PCI_D0)
		state = PCI_D0;
	else if ((state == PCI_D1 || state == PCI_D2) && pci_no_d1d2(dev))
		/*
		 * If the device or the parent bridge do not support PCI PM,
		 * ignore the request if we're doing anything other than putting
		 * it into D0 (which would only happen on boot).
		 */
		return 0;

	__pci_start_power_transition(dev, state);

	/* This device is quirked not to be put into D3, so
	   don't put it in D3 */
	if (state == PCI_D3hot && (dev->dev_flags & PCI_DEV_FLAGS_NO_D3))
		return 0;

	error = pci_raw_set_power_state(dev, state);

	if (!__pci_complete_power_transition(dev, state))
		error = 0;

	return error;
}