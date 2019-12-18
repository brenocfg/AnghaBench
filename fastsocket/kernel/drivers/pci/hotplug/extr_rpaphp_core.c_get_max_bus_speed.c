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
struct slot {int type; } ;
struct hotplug_slot {scalar_t__ private; } ;
typedef  enum pci_bus_speed { ____Placeholder_pci_bus_speed } pci_bus_speed ;

/* Variables and functions */
 int PCI_SPEED_100MHz_PCIX ; 
 int PCI_SPEED_133MHz_PCIX ; 
 int PCI_SPEED_33MHz ; 
 int PCI_SPEED_66MHz ; 
 int PCI_SPEED_66MHz_PCIX ; 
 int PCI_SPEED_UNKNOWN ; 

__attribute__((used)) static int get_max_bus_speed(struct hotplug_slot *hotplug_slot, enum pci_bus_speed *value)
{
	struct slot *slot = (struct slot *)hotplug_slot->private;

	switch (slot->type) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		*value = PCI_SPEED_33MHz;	/* speed for case 1-6 */
		break;
	case 7:
	case 8:
		*value = PCI_SPEED_66MHz;
		break;
	case 11:
	case 14:
		*value = PCI_SPEED_66MHz_PCIX;
		break;
	case 12:
	case 15:
		*value = PCI_SPEED_100MHz_PCIX;
		break;
	case 13:
	case 16:
		*value = PCI_SPEED_133MHz_PCIX;
		break;
	default:
		*value = PCI_SPEED_UNKNOWN;
		break;

	}
	return 0;
}