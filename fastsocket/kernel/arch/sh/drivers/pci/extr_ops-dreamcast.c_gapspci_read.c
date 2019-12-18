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
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAPSPCI_BBA_CONFIG ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  gapspci_config_access (int /*<<< orphan*/ ,unsigned int) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int inw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gapspci_read(struct pci_bus *bus, unsigned int devfn, int where, int size, u32 *val)
{
	*val = 0xffffffff;

	if (!gapspci_config_access(bus->number, devfn))
		return PCIBIOS_DEVICE_NOT_FOUND;

	switch (size) {
	case 1: *val = inb(GAPSPCI_BBA_CONFIG+where); break;
	case 2: *val = inw(GAPSPCI_BBA_CONFIG+where); break;
	case 4: *val = inl(GAPSPCI_BBA_CONFIG+where); break;
	}

        return PCIBIOS_SUCCESSFUL;
}