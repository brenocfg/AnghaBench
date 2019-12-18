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
 int /*<<< orphan*/  INTERPROCESSOR ; 
 int LAPIC_ICR_DM_NMI ; 
 int LAPIC_VECTOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAPIC_WRITE_ICR (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NMIPIs_enabled ; 
 int /*<<< orphan*/ * cpu_to_lapic ; 
 int /*<<< orphan*/  i386_cpu_IPI (int) ; 
 scalar_t__ ml_set_interrupts_enabled (scalar_t__) ; 

void
i386_send_NMI(int cpu)
{
	boolean_t state = ml_set_interrupts_enabled(FALSE);

	if (NMIPIs_enabled == FALSE) {
		i386_cpu_IPI(cpu);
	} else {
	/* Program the interrupt command register */
	/* The vector is ignored in this case--the target CPU will enter on the
	 * NMI vector.
	 */
	LAPIC_WRITE_ICR(cpu_to_lapic[cpu],
			LAPIC_VECTOR(INTERPROCESSOR)|LAPIC_ICR_DM_NMI);
	}
	(void) ml_set_interrupts_enabled(state);
}