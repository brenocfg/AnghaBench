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
typedef  scalar_t__ u32 ;
struct pci_controller {int dummy; } ;
struct pci_bus {int dummy; } ;
struct celleb_pci_resource {TYPE_1__* r; } ;
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
#define  PCI_BASE_ADDRESS_0 133 
#define  PCI_BASE_ADDRESS_1 132 
#define  PCI_BASE_ADDRESS_2 131 
#define  PCI_BASE_ADDRESS_3 130 
#define  PCI_BASE_ADDRESS_4 129 
#define  PCI_BASE_ADDRESS_5 128 
 int /*<<< orphan*/  celleb_config_write_fake (char*,int,int,scalar_t__) ; 
 char* get_fake_config_start (struct pci_controller*,unsigned int,unsigned int) ; 
 struct celleb_pci_resource* get_resource_start (struct pci_controller*,unsigned int,unsigned int) ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,scalar_t__) ; 

__attribute__((used)) static int celleb_fake_pci_write_config(struct pci_bus *bus,
		unsigned int devfn, int where, int size, u32 val)
{
	char *config;
	struct pci_controller *hose = pci_bus_to_host(bus);
	struct celleb_pci_resource *res;
	unsigned int devno = devfn >> 3;
	unsigned int fn = devfn & 0x7;

	/* allignment check */
	BUG_ON(where % size);

	config = get_fake_config_start(hose, devno, fn);

	if (!config)
		return PCIBIOS_DEVICE_NOT_FOUND;

	if (val == ~0) {
		int i = (where - PCI_BASE_ADDRESS_0) >> 3;

		switch (where) {
		case PCI_BASE_ADDRESS_0:
		case PCI_BASE_ADDRESS_2:
			if (size != 4)
				return PCIBIOS_DEVICE_NOT_FOUND;
			res = get_resource_start(hose, devno, fn);
			if (!res)
				return PCIBIOS_DEVICE_NOT_FOUND;
			celleb_config_write_fake(config, where, size,
					(res->r[i].end - res->r[i].start));
			return PCIBIOS_SUCCESSFUL;
		case PCI_BASE_ADDRESS_1:
		case PCI_BASE_ADDRESS_3:
		case PCI_BASE_ADDRESS_4:
		case PCI_BASE_ADDRESS_5:
			break;
		default:
			break;
		}
	}

	celleb_config_write_fake(config, where, size, val);
	pr_debug("    fake write: where=%x, size=%d, val=%x\n",
		 where, size, val);

	return PCIBIOS_SUCCESSFUL;
}