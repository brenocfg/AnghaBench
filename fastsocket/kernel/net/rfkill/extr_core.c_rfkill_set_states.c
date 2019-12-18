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
struct rfkill {int state; int persistent; int /*<<< orphan*/  uevent_work; int /*<<< orphan*/  registered; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int RFKILL_BLOCK_HW ; 
 int RFKILL_BLOCK_SW ; 
 int /*<<< orphan*/  __rfkill_set_sw_state (struct rfkill*,int) ; 
 int /*<<< orphan*/  rfkill_led_trigger_event (struct rfkill*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rfkill_set_states(struct rfkill *rfkill, bool sw, bool hw)
{
	unsigned long flags;
	bool swprev, hwprev;

	BUG_ON(!rfkill);

	spin_lock_irqsave(&rfkill->lock, flags);

	/*
	 * No need to care about prev/setblock ... this is for uevent only
	 * and that will get triggered by rfkill_set_block anyway.
	 */
	swprev = !!(rfkill->state & RFKILL_BLOCK_SW);
	hwprev = !!(rfkill->state & RFKILL_BLOCK_HW);
	__rfkill_set_sw_state(rfkill, sw);
	if (hw)
		rfkill->state |= RFKILL_BLOCK_HW;
	else
		rfkill->state &= ~RFKILL_BLOCK_HW;

	spin_unlock_irqrestore(&rfkill->lock, flags);

	if (!rfkill->registered) {
		rfkill->persistent = true;
	} else {
		if (swprev != sw || hwprev != hw)
			schedule_work(&rfkill->uevent_work);

		rfkill_led_trigger_event(rfkill);
	}
}