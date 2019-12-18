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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_is_root_bus (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_swizzle_interrupt_pin (struct pci_dev*,int /*<<< orphan*/ ) ; 

u8 pci_common_swizzle(struct pci_dev *dev, u8 *pinp)
{
	u8 pin = *pinp;

	while (!pci_is_root_bus(dev->bus)) {
		pin = pci_swizzle_interrupt_pin(dev, pin);
		dev = dev->bus->self;
	}
	*pinp = pin;
	return PCI_SLOT(dev->devfn);
}