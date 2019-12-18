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
struct cpumask {int dummy; } ;

/* Variables and functions */
 unsigned int BAD_APICID ; 
 int cpumask_first (struct cpumask const*) ; 
 unsigned int nr_cpu_ids ; 
 unsigned int per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  x86_cpu_to_logical_apicid ; 

__attribute__((used)) static unsigned int x2apic_cpu_mask_to_apicid(const struct cpumask *cpumask)
{
	/*
	 * We're using fixed IRQ delivery, can only return one logical APIC ID.
	 * May as well be the first.
	 */
	int cpu = cpumask_first(cpumask);

	if ((unsigned)cpu < nr_cpu_ids)
		return per_cpu(x86_cpu_to_logical_apicid, cpu);
	else
		return BAD_APICID;
}