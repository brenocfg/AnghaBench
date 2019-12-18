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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct slot {struct controller* ctrl; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_BUTTON_PRESS ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_interrupt_event (struct slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 

u8 pciehp_handle_attention_button(struct slot *p_slot)
{
	u32 event_type;
	struct controller *ctrl = p_slot->ctrl;

	/* Attention Button Change */
	ctrl_dbg(ctrl, "Attention button interrupt received\n");

	/*
	 *  Button pressed - See if need to TAKE ACTION!!!
	 */
	ctrl_info(ctrl, "Button pressed on Slot(%s)\n", slot_name(p_slot));
	event_type = INT_BUTTON_PRESS;

	queue_interrupt_event(p_slot, event_type);

	return 0;
}