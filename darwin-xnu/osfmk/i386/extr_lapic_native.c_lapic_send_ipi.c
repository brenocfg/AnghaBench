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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LAPIC_ICR_DM_FIXED ; 
 int LAPIC_ICR_DS_PENDING ; 
 int LAPIC_READ_ICR () ; 
 int /*<<< orphan*/  LAPIC_WRITE_ICR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_pause () ; 
 int /*<<< orphan*/ * cpu_to_lapic ; 
 int lapic_interrupt_base ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 

void
lapic_send_ipi(int cpu, int vector)
{
	boolean_t	state;

	if (vector < lapic_interrupt_base)
		vector += lapic_interrupt_base;

	state = ml_set_interrupts_enabled(FALSE);

	/* Wait for pending outgoing send to complete */
	while (LAPIC_READ_ICR() & LAPIC_ICR_DS_PENDING) {
		cpu_pause();
	}

	LAPIC_WRITE_ICR(cpu_to_lapic[cpu], vector | LAPIC_ICR_DM_FIXED);

	(void) ml_set_interrupts_enabled(state);
}