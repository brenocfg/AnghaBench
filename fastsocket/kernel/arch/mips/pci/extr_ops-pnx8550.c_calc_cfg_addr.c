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
 int PCI_CFG_BUS_SHIFT ; 
 unsigned int PCI_CFG_FUNC_SHIFT ; 

__attribute__((used)) static inline unsigned int
calc_cfg_addr(struct pci_bus *bus, unsigned int devfn, int where)
{
	unsigned int addr;

	addr = ((bus->number > 0) ? (((bus->number & 0xff) << PCI_CFG_BUS_SHIFT) | 1) : 0);
	addr |= ((devfn & 0xff) << PCI_CFG_FUNC_SHIFT) | (where & 0xfc);

	return addr;
}