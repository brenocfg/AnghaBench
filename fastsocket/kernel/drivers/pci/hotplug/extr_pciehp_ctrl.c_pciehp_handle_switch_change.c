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
 int /*<<< orphan*/  INT_SWITCH_CLOSE ; 
 int /*<<< orphan*/  INT_SWITCH_OPEN ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciehp_get_latch_status (struct slot*,int*) ; 
 int /*<<< orphan*/  queue_interrupt_event (struct slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 

u8 pciehp_handle_switch_change(struct slot *p_slot)
{
	u8 getstatus;
	u32 event_type;
	struct controller *ctrl = p_slot->ctrl;

	/* Switch Change */
	ctrl_dbg(ctrl, "Switch interrupt received\n");

	pciehp_get_latch_status(p_slot, &getstatus);
	if (getstatus) {
		/*
		 * Switch opened
		 */
		ctrl_info(ctrl, "Latch open on Slot(%s)\n", slot_name(p_slot));
		event_type = INT_SWITCH_OPEN;
	} else {
		/*
		 *  Switch closed
		 */
		ctrl_info(ctrl, "Latch close on Slot(%s)\n", slot_name(p_slot));
		event_type = INT_SWITCH_CLOSE;
	}

	queue_interrupt_event(p_slot, event_type);

	return 1;
}