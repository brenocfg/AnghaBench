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
typedef  enum rfkill_type { ____Placeholder_rfkill_type } rfkill_type ;

/* Variables and functions */
 int /*<<< orphan*/  __change_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rfkill_is_epo_lock_active () ; 
 int /*<<< orphan*/  rfkill_op_lock ; 
 int /*<<< orphan*/  rfkill_op_pending ; 
 int /*<<< orphan*/  rfkill_schedule_ratelimited () ; 
 int /*<<< orphan*/  rfkill_sw_pending ; 
 int /*<<< orphan*/  rfkill_sw_state ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rfkill_schedule_toggle(enum rfkill_type type)
{
	unsigned long flags;

	if (rfkill_is_epo_lock_active())
		return;

	spin_lock_irqsave(&rfkill_op_lock, flags);
	if (!rfkill_op_pending) {
		__set_bit(type, rfkill_sw_pending);
		__change_bit(type, rfkill_sw_state);
		rfkill_schedule_ratelimited();
	}
	spin_unlock_irqrestore(&rfkill_op_lock, flags);
}