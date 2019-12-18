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
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int /*<<< orphan*/  PCI_CMD_CONFIG_READ ; 
 int config_access (int /*<<< orphan*/ ,struct pci_bus*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
read_config_dword(struct pci_bus *bus, unsigned int devfn, int where, u32 * val)
{
	int err;
	if (bus == NULL)
		return -1;

	if (where & 0x03)
		return PCIBIOS_BAD_REGISTER_NUMBER;

	err = config_access(PCI_CMD_CONFIG_READ, bus, devfn, where, 0, val);

	return err;
}