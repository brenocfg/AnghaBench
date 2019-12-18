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
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (scalar_t__) ; 
 int /*<<< orphan*/  ml_spin_debug_clear_self () ; 

__attribute__((used)) static void
console_restore_interrupts_state(boolean_t state)
{
#if INTERRUPT_MASKED_DEBUG
	/*
	 * Serial console holds interrupts disabled for far too long
	 * and would trip the spin-debugger.  If we are about to reenable
	 * interrupts then clear the timer and avoid panicking on the delay.
	 * Otherwise, let the code that printed with interrupt disabled
	 * take the panic when it reenables interrupts.
	 * Hopefully one day this is fixed so that this workaround is unnecessary.
	 */
	if (state == TRUE)
		ml_spin_debug_clear_self();
#endif /* INTERRUPT_MASKED_DEBUG */
	ml_set_interrupts_enabled(state);
}