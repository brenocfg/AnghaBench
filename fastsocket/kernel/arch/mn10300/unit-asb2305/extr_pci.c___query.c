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
struct pci_bus {int number; } ;

/* Variables and functions */
 unsigned int PCI_DEVFN (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __query(const struct pci_bus *bus, unsigned int devfn)
{
#if 0
	return bus->number == 0 && (devfn == PCI_DEVFN(0, 0));
	return bus->number == 1;
	return bus->number == 0 &&
		(devfn == PCI_DEVFN(2, 0) || devfn == PCI_DEVFN(3, 0));
#endif
	return 1;
}