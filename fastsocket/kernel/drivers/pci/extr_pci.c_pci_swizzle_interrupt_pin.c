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
typedef  int u8 ;
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_ari_enabled (int /*<<< orphan*/ ) ; 

u8 pci_swizzle_interrupt_pin(struct pci_dev *dev, u8 pin)
{
	int slot;

	if (pci_ari_enabled(dev->bus))
		slot = 0;
	else
		slot = PCI_SLOT(dev->devfn);

	return (((pin - 1) + slot) % 4) + 1;
}