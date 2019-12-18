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
typedef  unsigned char u8 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CMD_CONFIG_READ ; 
 int config_access (int /*<<< orphan*/ ,struct pci_bus*,unsigned int,int,int,unsigned int*) ; 

__attribute__((used)) static int
read_config_byte(struct pci_bus *bus, unsigned int devfn, int where, u8 * val)
{
	unsigned int data = 0;
	int err;

	if (bus == NULL)
		return -1;

	err = config_access(PCI_CMD_CONFIG_READ, bus, devfn, where, ~(1 << (where & 3)), &data);
	switch (where & 0x03) {
	case 0:
		*val = (unsigned char)(data & 0x000000ff);
		break;
	case 1:
		*val = (unsigned char)((data & 0x0000ff00) >> 8);
		break;
	case 2:
		*val = (unsigned char)((data & 0x00ff0000) >> 16);
		break;
	case 3:
		*val = (unsigned char)((data & 0xff000000) >> 24);
		break;
	}

	return err;
}