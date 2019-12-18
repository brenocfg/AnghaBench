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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  pci_fixup_device (int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_fixup_enable ; 
 int pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pcibios_enable_device (struct pci_dev*,int) ; 

__attribute__((used)) static int do_pci_enable_device(struct pci_dev *dev, int bars)
{
	int err;

	err = pci_set_power_state(dev, PCI_D0);
	if (err < 0 && err != -EIO)
		return err;
	err = pcibios_enable_device(dev, bars);
	if (err < 0)
		return err;
	pci_fixup_device(pci_fixup_enable, dev);

	return 0;
}