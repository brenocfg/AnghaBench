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
typedef  int /*<<< orphan*/  u32 ;
struct pci_bus {int /*<<< orphan*/  number; scalar_t__ parent; } ;

/* Variables and functions */
 scalar_t__ CARDBUS_PCI_IDSEL ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 scalar_t__ PCI_SLOT (unsigned int) ; 
 int bcm63xx_do_cfg_read (int,int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm63xx_pci_read(struct pci_bus *bus, unsigned int devfn,
			     int where, int size, u32 *val)
{
	int type;

	type = bus->parent ? 1 : 0;

	if (type == 0 && PCI_SLOT(devfn) == CARDBUS_PCI_IDSEL)
		return PCIBIOS_DEVICE_NOT_FOUND;

	return bcm63xx_do_cfg_read(type, bus->number, devfn,
				    where, size, val);
}