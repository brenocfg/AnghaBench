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
struct pci_controller {int dummy; } ;
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  celleb_config_read_fake (char*,int,int,int /*<<< orphan*/ *) ; 
 char* get_fake_config_start (struct pci_controller*,unsigned int,unsigned int) ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int celleb_fake_pci_read_config(struct pci_bus *bus,
		unsigned int devfn, int where, int size, u32 *val)
{
	char *config;
	struct pci_controller *hose = pci_bus_to_host(bus);
	unsigned int devno = devfn >> 3;
	unsigned int fn = devfn & 0x7;

	/* allignment check */
	BUG_ON(where % size);

	pr_debug("    fake read: bus=0x%x, ", bus->number);
	config = get_fake_config_start(hose, devno, fn);

	pr_debug("devno=0x%x, where=0x%x, size=0x%x, ", devno, where, size);
	if (!config) {
		pr_debug("failed\n");
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	celleb_config_read_fake(config, where, size, val);
	pr_debug("val=0x%x\n", *val);

	return PCIBIOS_SUCCESSFUL;
}