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
typedef  int u16 ;
struct slot {struct controller* ctrl; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_SLTSTA ; 
 int PCI_EXP_SLTSTA_PFD ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*) ; 
 int pciehp_readw (struct controller*,int /*<<< orphan*/ ,int*) ; 

int pciehp_query_power_fault(struct slot *slot)
{
	struct controller *ctrl = slot->ctrl;
	u16 slot_status;
	int retval;

	retval = pciehp_readw(ctrl, PCI_EXP_SLTSTA, &slot_status);
	if (retval) {
		ctrl_err(ctrl, "Cannot check for power fault\n");
		return retval;
	}
	return !!(slot_status & PCI_EXP_SLTSTA_PFD);
}