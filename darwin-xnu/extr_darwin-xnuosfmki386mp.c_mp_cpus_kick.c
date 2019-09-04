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
typedef  int cpumask_t ;
typedef  scalar_t__ cpu_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KICK ; 
 int /*<<< orphan*/  LAPIC_VECTOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_is_running (scalar_t__) ; 
 scalar_t__ cpu_number () ; 
 int cpu_to_cpumask (scalar_t__) ; 
 int /*<<< orphan*/  lapic_send_ipi (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_safe_spin_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ real_ncpus ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_topo_lock ; 

void
mp_cpus_kick(cpumask_t cpus)
{
	cpu_t		cpu;
	boolean_t	intrs_enabled = FALSE;

	intrs_enabled = ml_set_interrupts_enabled(FALSE);
	mp_safe_spin_lock(&x86_topo_lock);

	for (cpu = 0; cpu < (cpu_t) real_ncpus; cpu++) {
		if ((cpu == (cpu_t) cpu_number())
			|| ((cpu_to_cpumask(cpu) & cpus) == 0)
			|| !cpu_is_running(cpu))
		{
				continue;
		}

		lapic_send_ipi(cpu, LAPIC_VECTOR(KICK));
	}

	simple_unlock(&x86_topo_lock);
	ml_set_interrupts_enabled(intrs_enabled);
}