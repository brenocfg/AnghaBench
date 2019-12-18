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
typedef  int /*<<< orphan*/  u32 ;
struct slot {struct controller* ctrl; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_POWER_FAULT ; 
 int /*<<< orphan*/  INT_POWER_FAULT_CLEAR ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciehp_query_power_fault (struct slot*) ; 
 int /*<<< orphan*/  queue_interrupt_event (struct slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 

u8 pciehp_handle_power_fault(struct slot *p_slot)
{
	u32 event_type;
	struct controller *ctrl = p_slot->ctrl;

	/* power fault */
	ctrl_dbg(ctrl, "Power fault interrupt received\n");

	if (!pciehp_query_power_fault(p_slot)) {
		/*
		 * power fault Cleared
		 */
		ctrl_info(ctrl, "Power fault cleared on Slot(%s)\n",
			  slot_name(p_slot));
		event_type = INT_POWER_FAULT_CLEAR;
	} else {
		/*
		 *   power fault
		 */
		ctrl_info(ctrl, "Power fault on Slot(%s)\n", slot_name(p_slot));
		event_type = INT_POWER_FAULT;
		ctrl_info(ctrl, "Power fault bit %x set\n", 0);
	}

	queue_interrupt_event(p_slot, event_type);

	return 1;
}