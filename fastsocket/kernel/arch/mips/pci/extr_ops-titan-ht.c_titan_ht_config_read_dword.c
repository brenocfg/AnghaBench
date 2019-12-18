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
typedef  int uint32_t ;
typedef  int u32 ;
struct pci_bus {int number; } ;
typedef  int int32_t ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int titan_ht_config_read_dword(struct pci_bus *bus, unsigned int devfn,
	int offset, u32 * val)
{
	volatile uint32_t address;
	int busno;

	busno = bus->number;

	address = (busno << 16) | (devfn << 8) | (offset & 0xfc) | 0x80000000;
	if (busno != 0)
		address |= 1;

	/*
	 * RM9000 HT Errata: Issue back to back HT config
	 * transcations. Issue a BIU sync before and
	 * after the HT cycle
	 */

	*(volatile int32_t *) 0xfb0000f0 |= 0x2;

	udelay(30);

	*(volatile int32_t *) 0xfb0006f8 = address;
	*(val) = *(volatile int32_t *) 0xfb0006fc;

	udelay(30);

	* (volatile int32_t *) 0xfb0000f0 |= 0x2;

	return PCIBIOS_SUCCESSFUL;
}