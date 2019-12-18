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
struct pci_func {int presence_save; int switch_save; } ;
struct event_info {int hp_slot; int /*<<< orphan*/  event_type; } ;
struct controller {size_t next_event; int ctrl_int_comp; struct event_info* event_queue; scalar_t__ slot_device_offset; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_SWITCH_CLOSE ; 
 int /*<<< orphan*/  INT_SWITCH_OPEN ; 
 struct pci_func* cpqhp_slot_find (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*) ; 

__attribute__((used)) static u8 handle_switch_change(u8 change, struct controller * ctrl)
{
	int hp_slot;
	u8 rc = 0;
	u16 temp_word;
	struct pci_func *func;
	struct event_info *taskInfo;

	if (!change)
		return 0;

	/* Switch Change */
	dbg("cpqsbd:  Switch interrupt received.\n");

	for (hp_slot = 0; hp_slot < 6; hp_slot++) {
		if (change & (0x1L << hp_slot)) {
			/*
			 * this one changed.
			 */
			func = cpqhp_slot_find(ctrl->bus,
				(hp_slot + ctrl->slot_device_offset), 0);

			/* this is the structure that tells the worker thread
			 * what to do
			 */
			taskInfo = &(ctrl->event_queue[ctrl->next_event]);
			ctrl->next_event = (ctrl->next_event + 1) % 10;
			taskInfo->hp_slot = hp_slot;

			rc++;

			temp_word = ctrl->ctrl_int_comp >> 16;
			func->presence_save = (temp_word >> hp_slot) & 0x01;
			func->presence_save |= (temp_word >> (hp_slot + 7)) & 0x02;

			if (ctrl->ctrl_int_comp & (0x1L << hp_slot)) {
				/*
				 * Switch opened
				 */

				func->switch_save = 0;

				taskInfo->event_type = INT_SWITCH_OPEN;
			} else {
				/*
				 * Switch closed
				 */

				func->switch_save = 0x10;

				taskInfo->event_type = INT_SWITCH_CLOSE;
			}
		}
	}

	return rc;
}