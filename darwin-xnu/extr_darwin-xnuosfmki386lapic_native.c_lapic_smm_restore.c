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
 scalar_t__ FALSE ; 
 scalar_t__ LAPIC_ISR_IS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LAPIC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAPIC_REDUCED_INTERRUPT_BASE ; 
 int /*<<< orphan*/  LAPIC_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TIMER ; 
 int /*<<< orphan*/  TIMER_CURRENT_COUNT ; 
 int /*<<< orphan*/  TIMER_INITIAL_COUNT ; 
 int /*<<< orphan*/  _lapic_end_of_interrupt () ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 scalar_t__ lapic_os_enabled ; 
 scalar_t__ ml_set_interrupts_enabled (scalar_t__) ; 

void
lapic_smm_restore(void)
{
	boolean_t state;

	if (lapic_os_enabled == FALSE)
		return;

	state = ml_set_interrupts_enabled(FALSE);

 	if (LAPIC_ISR_IS_SET(LAPIC_REDUCED_INTERRUPT_BASE, TIMER)) {
		/*
		 * Bogus SMI handler enables interrupts but does not know about
		 * local APIC interrupt sources. When APIC timer counts down to
		 * zero while in SMM, local APIC will end up waiting for an EOI
		 * but no interrupt was delivered to the OS.
 		 */
		_lapic_end_of_interrupt();

		/*
		 * timer is one-shot, trigger another quick countdown to trigger
		 * another timer interrupt.
		 */
		if (LAPIC_READ(TIMER_CURRENT_COUNT) == 0) {
			LAPIC_WRITE(TIMER_INITIAL_COUNT, 1);
		}

		kprintf("lapic_smm_restore\n");
	}

	ml_set_interrupts_enabled(state);
}