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
 int MAX_CPUS ; 
 int MAX_LAPICIDS ; 
 int /*<<< orphan*/  assert (int) ; 
 int* cpu_to_lapic ; 
 int* lapic_to_cpu ; 

void
lapic_cpu_map(int apic_id, int cpu)
{
	assert(apic_id < MAX_LAPICIDS);
	assert(cpu < MAX_CPUS);
	cpu_to_lapic[cpu] = apic_id;
	lapic_to_cpu[apic_id] = cpu;
}