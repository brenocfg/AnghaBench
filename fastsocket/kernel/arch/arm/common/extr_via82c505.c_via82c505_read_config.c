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
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CMD (struct pci_bus*,unsigned int,int) ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  inb (int) ; 
 int /*<<< orphan*/  inl (int) ; 
 int /*<<< orphan*/  inw (int) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
via82c505_read_config(struct pci_bus *bus, unsigned int devfn, int where,
		      int size, u32 *value)
{
	outl(CONFIG_CMD(bus,devfn,where),0xCF8);
	switch (size) {
	case 1:
		*value=inb(0xCFC + (where&3));
		break;
	case 2:
		*value=inw(0xCFC + (where&2));
		break;
	case 4:
		*value=inl(0xCFC);
		break;
	}
	return PCIBIOS_SUCCESSFUL;
}