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
typedef  int u32 ;
struct slot {struct controller* ctrl; } ;
struct controller {int dummy; } ;
typedef  enum pci_bus_speed { ____Placeholder_pci_bus_speed } pci_bus_speed ;

/* Variables and functions */
 int ENODEV ; 
 int PCI_SPEED_100MHz_PCIX ; 
 int PCI_SPEED_100MHz_PCIX_266 ; 
 int PCI_SPEED_100MHz_PCIX_533 ; 
 int PCI_SPEED_133MHz_PCIX ; 
 int PCI_SPEED_133MHz_PCIX_266 ; 
 int PCI_SPEED_133MHz_PCIX_533 ; 
 int PCI_SPEED_33MHz ; 
 int PCI_SPEED_66MHz ; 
 int PCI_SPEED_66MHz_PCIX ; 
 int PCI_SPEED_66MHz_PCIX_266 ; 
 int PCI_SPEED_66MHz_PCIX_533 ; 
 int PCI_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  PROG_INTERFACE ; 
 int SLOT_100MHZ_PCIX ; 
 int SLOT_100MHZ_PCIX_266 ; 
 int SLOT_100MHZ_PCIX_533 ; 
 int SLOT_133MHZ_PCIX ; 
 int SLOT_133MHZ_PCIX_266 ; 
 int SLOT_133MHZ_PCIX_533 ; 
 int SLOT_33MHZ ; 
 int SLOT_66MHZ ; 
 int SLOT_66MHZ_PCIX ; 
 int SLOT_66MHZ_PCIX_266 ; 
 int SLOT_66MHZ_PCIX_533 ; 
 int /*<<< orphan*/  SLOT_AVAIL1 ; 
 int /*<<< orphan*/  SLOT_AVAIL2 ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*,int) ; 
 int shpc_readb (struct controller*,int /*<<< orphan*/ ) ; 
 int shpc_readl (struct controller*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpc_get_max_bus_speed (struct slot *slot, enum pci_bus_speed *value)
{
	int retval = 0;
	struct controller *ctrl = slot->ctrl;
	enum pci_bus_speed bus_speed = PCI_SPEED_UNKNOWN;
	u8 pi = shpc_readb(ctrl, PROG_INTERFACE);
	u32 slot_avail1 = shpc_readl(ctrl, SLOT_AVAIL1);
	u32 slot_avail2 = shpc_readl(ctrl, SLOT_AVAIL2);

	if (pi == 2) {
		if (slot_avail2 & SLOT_133MHZ_PCIX_533)
			bus_speed = PCI_SPEED_133MHz_PCIX_533;
		else if (slot_avail2 & SLOT_100MHZ_PCIX_533)
			bus_speed = PCI_SPEED_100MHz_PCIX_533;
		else if (slot_avail2 & SLOT_66MHZ_PCIX_533)
			bus_speed = PCI_SPEED_66MHz_PCIX_533;
		else if (slot_avail2 & SLOT_133MHZ_PCIX_266)
			bus_speed = PCI_SPEED_133MHz_PCIX_266;
		else if (slot_avail2 & SLOT_100MHZ_PCIX_266)
			bus_speed = PCI_SPEED_100MHz_PCIX_266;
		else if (slot_avail2 & SLOT_66MHZ_PCIX_266)
			bus_speed = PCI_SPEED_66MHz_PCIX_266;
	}

	if (bus_speed == PCI_SPEED_UNKNOWN) {
		if (slot_avail1 & SLOT_133MHZ_PCIX)
			bus_speed = PCI_SPEED_133MHz_PCIX;
		else if (slot_avail1 & SLOT_100MHZ_PCIX)
			bus_speed = PCI_SPEED_100MHz_PCIX;
		else if (slot_avail1 & SLOT_66MHZ_PCIX)
			bus_speed = PCI_SPEED_66MHz_PCIX;
		else if (slot_avail2 & SLOT_66MHZ)
			bus_speed = PCI_SPEED_66MHz;
		else if (slot_avail1 & SLOT_33MHZ)
			bus_speed = PCI_SPEED_33MHz;
		else
			retval = -ENODEV;
	}

	*value = bus_speed;
	ctrl_dbg(ctrl, "Max bus speed = %d\n", bus_speed);

	return retval;
}