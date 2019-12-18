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
struct iowa_bus {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {int /*<<< orphan*/  pgd; } ;
typedef  int /*<<< orphan*/  PCI_IO_ADDR ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 scalar_t__ PCI_FIX_ADDR (int /*<<< orphan*/  const) ; 
 int PCI_GET_ADDR_TOKEN (int /*<<< orphan*/  const) ; 
 unsigned long PHB_IO_BASE ; 
 unsigned long PHB_IO_END ; 
 int /*<<< orphan*/ * find_linux_pte (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__ init_mm ; 
 int iowa_bus_count ; 
 struct iowa_bus* iowa_busses ; 
 struct iowa_bus* iowa_pci_find (unsigned long,unsigned long) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 

struct iowa_bus *iowa_mem_find_bus(const PCI_IO_ADDR addr)
{
	struct iowa_bus *bus;
	int token;

	token = PCI_GET_ADDR_TOKEN(addr);

	if (token && token <= iowa_bus_count)
		bus = &iowa_busses[token - 1];
	else {
		unsigned long vaddr, paddr;
		pte_t *ptep;

		vaddr = (unsigned long)PCI_FIX_ADDR(addr);
		if (vaddr < PHB_IO_BASE || vaddr >= PHB_IO_END)
			return NULL;

		ptep = find_linux_pte(init_mm.pgd, vaddr);
		if (ptep == NULL)
			paddr = 0;
		else
			paddr = pte_pfn(*ptep) << PAGE_SHIFT;
		bus = iowa_pci_find(vaddr, paddr);

		if (bus == NULL)
			return NULL;
	}

	return bus;
}