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
typedef  scalar_t__ u32 ;
struct pci_bus {scalar_t__ number; } ;

/* Variables and functions */
 scalar_t__ LDT_BRIDGE_DEVICE ; 
 int LDT_BUS_ENABLED ; 
 int PCI_BUS_ENABLED ; 
 int PCI_DEVICE_MODE ; 
 scalar_t__ PCI_SLOT (int) ; 
 int sb1250_bus_status ; 

__attribute__((used)) static int sb1250_pci_can_access(struct pci_bus *bus, int devfn)
{
	u32 devno;

	if (!(sb1250_bus_status & (PCI_BUS_ENABLED | PCI_DEVICE_MODE)))
		return 0;

	if (bus->number == 0) {
		devno = PCI_SLOT(devfn);
		if (devno == LDT_BRIDGE_DEVICE)
			return (sb1250_bus_status & LDT_BUS_ENABLED) != 0;
		else if (sb1250_bus_status & PCI_DEVICE_MODE)
			return 0;
		else
			return 1;
	} else
		return 1;
}