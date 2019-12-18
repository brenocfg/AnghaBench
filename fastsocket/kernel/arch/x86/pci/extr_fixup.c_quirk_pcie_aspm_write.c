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
typedef  int u8 ;
typedef  int u32 ;
struct pci_bus {int /*<<< orphan*/  number; TYPE_1__* self; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 size_t GET_INDEX (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 int* quirk_aspm_offset ; 
 int raw_pci_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int) ; 

__attribute__((used)) static int quirk_pcie_aspm_write(struct pci_bus *bus, unsigned int devfn, int where, int size, u32 value)
{
	u8 offset;

	offset = quirk_aspm_offset[GET_INDEX(bus->self->device, devfn)];

	if ((offset) && (where == offset))
		value = value & 0xfffffffc;

	return raw_pci_write(pci_domain_nr(bus), bus->number,
						devfn, where, size, value);
}