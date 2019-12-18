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
struct rfkill {int state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int RFKILL_BLOCK_ANY ; 
 int RFKILL_BLOCK_HW ; 
 int /*<<< orphan*/  rfkill_led_trigger_event (struct rfkill*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool __rfkill_set_hw_state(struct rfkill *rfkill,
				  bool blocked, bool *change)
{
	unsigned long flags;
	bool prev, any;

	BUG_ON(!rfkill);

	spin_lock_irqsave(&rfkill->lock, flags);
	prev = !!(rfkill->state & RFKILL_BLOCK_HW);
	if (blocked)
		rfkill->state |= RFKILL_BLOCK_HW;
	else
		rfkill->state &= ~RFKILL_BLOCK_HW;
	*change = prev != blocked;
	any = rfkill->state & RFKILL_BLOCK_ANY;
	spin_unlock_irqrestore(&rfkill->lock, flags);

	rfkill_led_trigger_event(rfkill);

	return any;
}