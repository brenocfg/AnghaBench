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
struct rfkill {int state; int /*<<< orphan*/  uevent_work; int /*<<< orphan*/  registered; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int RFKILL_BLOCK_HW ; 
 int RFKILL_BLOCK_SW ; 
 int /*<<< orphan*/  __rfkill_set_sw_state (struct rfkill*,int) ; 
 int /*<<< orphan*/  rfkill_led_trigger_event (struct rfkill*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool rfkill_set_sw_state(struct rfkill *rfkill, bool blocked)
{
	unsigned long flags;
	bool prev, hwblock;

	BUG_ON(!rfkill);

	spin_lock_irqsave(&rfkill->lock, flags);
	prev = !!(rfkill->state & RFKILL_BLOCK_SW);
	__rfkill_set_sw_state(rfkill, blocked);
	hwblock = !!(rfkill->state & RFKILL_BLOCK_HW);
	blocked = blocked || hwblock;
	spin_unlock_irqrestore(&rfkill->lock, flags);

	if (!rfkill->registered)
		return blocked;

	if (prev != blocked && !hwblock)
		schedule_work(&rfkill->uevent_work);

	rfkill_led_trigger_event(rfkill);

	return blocked;
}