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
struct pci_controller {unsigned long config_space_base; int /*<<< orphan*/  index; } ;
struct pci_bus {int number; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_CFG (char*) ; 

__attribute__((used)) static int
mk_conf_addr(struct pci_bus *pbus, unsigned int devfn, int where,
	     struct pci_controller *hose, unsigned long *pci_addr,
	     unsigned char *type1)
{
	u8 bus = pbus->number;
	unsigned long addr;

	DBG_CFG(("mk_conf_addr(bus=%d,devfn=0x%x,hose=%d,where=0x%x,"
		 " pci_addr=0x%p, type1=0x%p)\n",
		 bus, devfn, hose->index, where, pci_addr, type1));

	/* Type 1 configuration cycle for *ALL* busses.  */
	*type1 = 1;

	if (!pbus->parent) /* No parent means peer PCI bus. */
		bus = 0;
	addr = (bus << 16) | (devfn << 8) | (where);
	addr <<= 5; /* swizzle for SPARSE */
	addr |= hose->config_space_base;

	*pci_addr = addr;
	DBG_CFG(("mk_conf_addr: returning pci_addr 0x%lx\n", addr));
	return 0;
}