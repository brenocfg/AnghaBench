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
 int /*<<< orphan*/  INT_PRESENCE_OFF ; 
 int /*<<< orphan*/  INT_PRESENCE_ON ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciehp_get_adapter_status (struct slot*,int*) ; 
 int /*<<< orphan*/  queue_interrupt_event (struct slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 

u8 pciehp_handle_presence_change(struct slot *p_slot)
{
	u32 event_type;
	u8 presence_save;
	struct controller *ctrl = p_slot->ctrl;

	/* Presence Change */
	ctrl_dbg(ctrl, "Presence/Notify input change\n");

	/* Switch is open, assume a presence change
	 * Save the presence state
	 */
	pciehp_get_adapter_status(p_slot, &presence_save);
	if (presence_save) {
		/*
		 * Card Present
		 */
		ctrl_info(ctrl, "Card present on Slot(%s)\n", slot_name(p_slot));
		event_type = INT_PRESENCE_ON;
	} else {
		/*
		 * Not Present
		 */
		ctrl_info(ctrl, "Card not present on Slot(%s)\n",
			  slot_name(p_slot));
		event_type = INT_PRESENCE_OFF;
	}

	queue_interrupt_event(p_slot, event_type);

	return 1;
}