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
typedef  scalar_t__ u16 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int /*<<< orphan*/  PCI_CMD_CONFIG_WRITE ; 
 int config_access (int /*<<< orphan*/ ,struct pci_bus*,unsigned int,int,int,unsigned int*) ; 

__attribute__((used)) static int
write_config_word(struct pci_bus *bus, unsigned int devfn, int where, u16 val)
{
	unsigned int data = (unsigned int)val;
	int err;

	if (bus == NULL)
		return -1;

	if (where & 0x01)
		return PCIBIOS_BAD_REGISTER_NUMBER;

	switch (where & 0x02) {
	case 2:
		data = (data << 16);
		break;
	default:
		break;
	}
	err = config_access(PCI_CMD_CONFIG_WRITE, bus, devfn, where, ~(3 << (where & 3)), &data);

	return err;
}