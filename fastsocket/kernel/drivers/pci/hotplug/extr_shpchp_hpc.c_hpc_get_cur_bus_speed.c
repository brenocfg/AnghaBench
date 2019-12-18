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
typedef  int u8 ;
typedef  int u16 ;
struct slot {struct controller* ctrl; } ;
struct controller {int dummy; } ;
typedef  enum pci_bus_speed { ____Placeholder_pci_bus_speed } pci_bus_speed ;

/* Variables and functions */
 int ENODEV ; 
 int PCI_SPEED_100MHz_PCIX ; 
 int PCI_SPEED_100MHz_PCIX_266 ; 
 int PCI_SPEED_100MHz_PCIX_533 ; 
 int PCI_SPEED_100MHz_PCIX_ECC ; 
 int PCI_SPEED_133MHz_PCIX ; 
 int PCI_SPEED_133MHz_PCIX_266 ; 
 int PCI_SPEED_133MHz_PCIX_533 ; 
 int PCI_SPEED_133MHz_PCIX_ECC ; 
 int PCI_SPEED_33MHz ; 
 int PCI_SPEED_66MHz ; 
 int PCI_SPEED_66MHz_PCIX ; 
 int PCI_SPEED_66MHz_PCIX_266 ; 
 int PCI_SPEED_66MHz_PCIX_533 ; 
 int PCI_SPEED_66MHz_PCIX_ECC ; 
 int PCI_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  PROG_INTERFACE ; 
 int /*<<< orphan*/  SEC_BUS_CONFIG ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*,int) ; 
 int shpc_readb (struct controller*,int /*<<< orphan*/ ) ; 
 int shpc_readw (struct controller*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpc_get_cur_bus_speed (struct slot *slot, enum pci_bus_speed *value)
{
	int retval = 0;
	struct controller *ctrl = slot->ctrl;
	enum pci_bus_speed bus_speed = PCI_SPEED_UNKNOWN;
	u16 sec_bus_reg = shpc_readw(ctrl, SEC_BUS_CONFIG);
	u8 pi = shpc_readb(ctrl, PROG_INTERFACE);
	u8 speed_mode = (pi == 2) ? (sec_bus_reg & 0xF) : (sec_bus_reg & 0x7);

	if ((pi == 1) && (speed_mode > 4)) {
		*value = PCI_SPEED_UNKNOWN;
		return -ENODEV;
	}

	switch (speed_mode) {
	case 0x0:
		*value = PCI_SPEED_33MHz;
		break;
	case 0x1:
		*value = PCI_SPEED_66MHz;
		break;
	case 0x2:
		*value = PCI_SPEED_66MHz_PCIX;
		break;
	case 0x3:
		*value = PCI_SPEED_100MHz_PCIX;
		break;
	case 0x4:
		*value = PCI_SPEED_133MHz_PCIX;
		break;
	case 0x5:
		*value = PCI_SPEED_66MHz_PCIX_ECC;
		break;
	case 0x6:
		*value = PCI_SPEED_100MHz_PCIX_ECC;
		break;
	case 0x7:
		*value = PCI_SPEED_133MHz_PCIX_ECC;
		break;
	case 0x8:
		*value = PCI_SPEED_66MHz_PCIX_266;
		break;
	case 0x9:
		*value = PCI_SPEED_100MHz_PCIX_266;
		break;
	case 0xa:
		*value = PCI_SPEED_133MHz_PCIX_266;
		break;
	case 0xb:
		*value = PCI_SPEED_66MHz_PCIX_533;
		break;
	case 0xc:
		*value = PCI_SPEED_100MHz_PCIX_533;
		break;
	case 0xd:
		*value = PCI_SPEED_133MHz_PCIX_533;
		break;
	default:
		*value = PCI_SPEED_UNKNOWN;
		retval = -ENODEV;
		break;
	}

	ctrl_dbg(ctrl, "Current bus speed = %d\n", bus_speed);
	return retval;
}