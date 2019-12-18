#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct slot {int /*<<< orphan*/  presence_save; TYPE_1__* hpc_ops; } ;
struct controller {scalar_t__ slot_device_offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_adapter_status ) (struct slot*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INT_BUTTON_PRESS ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_interrupt_event (struct slot*,int /*<<< orphan*/ ) ; 
 struct slot* shpchp_find_slot (struct controller*,scalar_t__) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 
 int /*<<< orphan*/  stub1 (struct slot*,int /*<<< orphan*/ *) ; 

u8 shpchp_handle_attention_button(u8 hp_slot, struct controller *ctrl)
{
	struct slot *p_slot;
	u32 event_type;

	/* Attention Button Change */
	ctrl_dbg(ctrl, "Attention button interrupt received\n");

	p_slot = shpchp_find_slot(ctrl, hp_slot + ctrl->slot_device_offset);
	p_slot->hpc_ops->get_adapter_status(p_slot, &(p_slot->presence_save));

	/*
	 *  Button pressed - See if need to TAKE ACTION!!!
	 */
	ctrl_info(ctrl, "Button pressed on Slot(%s)\n", slot_name(p_slot));
	event_type = INT_BUTTON_PRESS;

	queue_interrupt_event(p_slot, event_type);

	return 0;

}