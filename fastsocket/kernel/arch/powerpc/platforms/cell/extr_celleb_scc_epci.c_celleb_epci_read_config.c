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
struct pci_controller {scalar_t__ first_busno; } ;
struct pci_bus {scalar_t__ number; } ;
typedef  scalar_t__ PCI_IO_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int celleb_epci_check_abort (struct pci_controller*,int /*<<< orphan*/ *) ; 
 scalar_t__ celleb_epci_get_epci_base (struct pci_controller*) ; 
 int /*<<< orphan*/  celleb_epci_get_epci_cfg (struct pci_controller*) ; 
 scalar_t__ celleb_epci_make_config_addr (struct pci_bus*,struct pci_controller*,unsigned int,int) ; 
 int /*<<< orphan*/  clear_and_disable_master_abort_interrupt (struct pci_controller*) ; 
 int /*<<< orphan*/  in_8 (scalar_t__) ; 
 int /*<<< orphan*/  in_be16 (scalar_t__) ; 
 int /*<<< orphan*/  in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  in_le16 (scalar_t__) ; 
 int /*<<< orphan*/  in_le32 (scalar_t__) ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,unsigned int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int celleb_epci_read_config(struct pci_bus *bus,
			unsigned int devfn, int where, int size, u32 *val)
{
	PCI_IO_ADDR epci_base;
	PCI_IO_ADDR addr;
	struct pci_controller *hose = pci_bus_to_host(bus);

	/* allignment check */
	BUG_ON(where % size);

	if (!celleb_epci_get_epci_cfg(hose))
		return PCIBIOS_DEVICE_NOT_FOUND;

	if (bus->number == hose->first_busno && devfn == 0) {
		/* EPCI controller self */

		epci_base = celleb_epci_get_epci_base(hose);
		addr = epci_base + where;

		switch (size) {
		case 1:
			*val = in_8(addr);
			break;
		case 2:
			*val = in_be16(addr);
			break;
		case 4:
			*val = in_be32(addr);
			break;
		default:
			return PCIBIOS_DEVICE_NOT_FOUND;
		}

	} else {

		clear_and_disable_master_abort_interrupt(hose);
		addr = celleb_epci_make_config_addr(bus, hose, devfn, where);

		switch (size) {
		case 1:
			*val = in_8(addr);
			break;
		case 2:
			*val = in_le16(addr);
			break;
		case 4:
			*val = in_le32(addr);
			break;
		default:
			return PCIBIOS_DEVICE_NOT_FOUND;
		}
	}

	pr_debug("EPCI: "
		 "addr=0x%p, devfn=0x%x, where=0x%x, size=0x%x, val=0x%x\n",
		 addr, devfn, where, size, *val);

	return celleb_epci_check_abort(hose, NULL);
}