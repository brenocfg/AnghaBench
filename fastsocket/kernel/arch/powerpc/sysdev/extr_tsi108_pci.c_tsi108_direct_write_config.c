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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_controller {int dummy; } ;
struct pci_bus {int /*<<< orphan*/  number; } ;
struct TYPE_2__ {scalar_t__ (* pci_exclude_device ) (struct pci_controller*,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_le16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ stub1 (struct pci_controller*,int /*<<< orphan*/ ,unsigned int) ; 
 int tsi_mk_config_addr (int /*<<< orphan*/ ,unsigned int,int) ; 

int
tsi108_direct_write_config(struct pci_bus *bus, unsigned int devfunc,
			   int offset, int len, u32 val)
{
	volatile unsigned char *cfg_addr;
	struct pci_controller *hose = pci_bus_to_host(bus);

	if (ppc_md.pci_exclude_device)
		if (ppc_md.pci_exclude_device(hose, bus->number, devfunc))
			return PCIBIOS_DEVICE_NOT_FOUND;

	cfg_addr = (unsigned char *)(tsi_mk_config_addr(bus->number,
							devfunc, offset) |
							(offset & 0x03));

#ifdef DEBUG
	printk("PCI CFG write : ");
	printk("%d:0x%x:0x%x ", bus->number, devfunc, offset);
	printk("%d ADDR=0x%08x ", len, (uint) cfg_addr);
	printk("data = 0x%08x\n", val);
#endif

	switch (len) {
	case 1:
		out_8((u8 *) cfg_addr, val);
		break;
	case 2:
		out_le16((u16 *) cfg_addr, val);
		break;
	default:
		out_le32((u32 *) cfg_addr, val);
		break;
	}

	return PCIBIOS_SUCCESSFUL;
}