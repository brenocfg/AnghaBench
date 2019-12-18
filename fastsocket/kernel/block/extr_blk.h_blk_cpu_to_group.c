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
 int NR_CPUS ; 
 struct cpumask* cpu_coregroup_mask (int) ; 
 int cpumask_first (struct cpumask const*) ; 
 scalar_t__ likely (int) ; 
 struct cpumask const* topology_thread_cpumask (int) ; 

__attribute__((used)) static inline int blk_cpu_to_group(int cpu)
{
	int group = NR_CPUS;
#ifdef CONFIG_SCHED_MC
	const struct cpumask *mask = cpu_coregroup_mask(cpu);
	group = cpumask_first(mask);
#elif defined(CONFIG_SCHED_SMT)
	group = cpumask_first(topology_thread_cpumask(cpu));
#else
	return cpu;
#endif

	if (likely(group < NR_CPUS))
		return group;
	return cpu;
}