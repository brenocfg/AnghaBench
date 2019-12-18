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
typedef  int u32 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int* CSR_PCICMD ; 
 int PCIBIOS_SUCCESSFUL ; 
 int PCICMD_ABORT ; 
 unsigned long dc21285_base_address (struct pci_bus*,unsigned int) ; 

__attribute__((used)) static int
dc21285_write_config(struct pci_bus *bus, unsigned int devfn, int where,
		     int size, u32 value)
{
	unsigned long addr = dc21285_base_address(bus, devfn);
	u32 v;

	if (addr)
		switch (size) {
		case 1:
			asm("strb	%0, [%1, %2]"
				: : "r" (value), "r" (addr), "r" (where)
				: "cc");
			break;
		case 2:
			asm("strh	%0, [%1, %2]"
				: : "r" (value), "r" (addr), "r" (where)
				: "cc");
			break;
		case 4:
			asm("str	%0, [%1, %2]"
				: : "r" (value), "r" (addr), "r" (where)
				: "cc");
			break;
		}

	v = *CSR_PCICMD;
	if (v & PCICMD_ABORT) {
		*CSR_PCICMD = v & (0xffff|PCICMD_ABORT);
		return -1;
	}

	return PCIBIOS_SUCCESSFUL;
}