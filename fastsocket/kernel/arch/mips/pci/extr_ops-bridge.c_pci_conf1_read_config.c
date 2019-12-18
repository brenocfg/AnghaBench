#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct pci_bus {int number; } ;
struct bridge_controller {TYPE_2__* base; } ;
struct TYPE_3__ {void* c; } ;
struct TYPE_4__ {int b_pci_cfg; TYPE_1__ b_type1_cfg; } ;
typedef  TYPE_2__ bridge_t ;

/* Variables and functions */
 struct bridge_controller* BRIDGE_CONTROLLER (struct pci_bus*) ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int PCI_DEVICE_ID_SGI_IOC3 ; 
 int PCI_FUNC (unsigned int) ; 
 int PCI_SLOT (unsigned int) ; 
 int PCI_VENDOR_ID ; 
 int PCI_VENDOR_ID_SGI ; 
 int emulate_ioc3_cfg (int,int) ; 
 int get_dbe (int,int*) ; 

__attribute__((used)) static int pci_conf1_read_config(struct pci_bus *bus, unsigned int devfn,
				 int where, int size, u32 * value)
{
	struct bridge_controller *bc = BRIDGE_CONTROLLER(bus);
	bridge_t *bridge = bc->base;
	int busno = bus->number;
	int slot = PCI_SLOT(devfn);
	int fn = PCI_FUNC(devfn);
	volatile void *addr;
	u32 cf, shift, mask;
	int res;

	bridge->b_pci_cfg = (busno << 16) | (slot << 11);
	addr = &bridge->b_type1_cfg.c[(fn << 8) | PCI_VENDOR_ID];
	if (get_dbe(cf, (u32 *) addr))
		return PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * IOC3 is fucked fucked beyond believe ...  Don't even give the
	 * generic PCI code a chance to look at it for real ...
	 */
	if (cf == (PCI_VENDOR_ID_SGI | (PCI_DEVICE_ID_SGI_IOC3 << 16)))
		goto oh_my_gawd;

	bridge->b_pci_cfg = (busno << 16) | (slot << 11);
	addr = &bridge->b_type1_cfg.c[(fn << 8) | (where ^ (4 - size))];

	if (size == 1)
		res = get_dbe(*value, (u8 *) addr);
	else if (size == 2)
		res = get_dbe(*value, (u16 *) addr);
	else
		res = get_dbe(*value, (u32 *) addr);

	return res ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUL;

oh_my_gawd:

	/*
	 * IOC3 is fucked fucked beyond believe ...  Don't even give the
	 * generic PCI code a chance to look at the wrong register.
	 */
	if ((where >= 0x14 && where < 0x40) || (where >= 0x48)) {
		*value = emulate_ioc3_cfg(where, size);
		return PCIBIOS_SUCCESSFUL;
	}

	/*
	 * IOC3 is fucked fucked beyond believe ...  Don't try to access
	 * anything but 32-bit words ...
	 */
	bridge->b_pci_cfg = (busno << 16) | (slot << 11);
	addr = &bridge->b_type1_cfg.c[(fn << 8) | where];

	if (get_dbe(cf, (u32 *) addr))
		return PCIBIOS_DEVICE_NOT_FOUND;

	shift = ((where & 3) << 3);
	mask = (0xffffffffU >> ((4 - size) << 3));
	*value = (cf >> shift) & mask;

	return PCIBIOS_SUCCESSFUL;
}