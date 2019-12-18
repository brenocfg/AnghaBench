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

/* Variables and functions */
 int STATE_SLOT_COUNT ; 
 scalar_t__ emu_check_save_file (int,scalar_t__*) ; 
 int state_slot_flags ; 
 scalar_t__* state_slot_times ; 

__attribute__((used)) static void state_check_slots(void)
{
	int slot;

	state_slot_flags = 0;

	for (slot = 0; slot < STATE_SLOT_COUNT; slot++) {
		state_slot_times[slot] = 0;
		if (emu_check_save_file(slot, &state_slot_times[slot]))
			state_slot_flags |= 1 << slot;
	}
}