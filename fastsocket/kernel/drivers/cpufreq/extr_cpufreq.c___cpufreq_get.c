#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpufreq_policy {unsigned int cur; int /*<<< orphan*/  update; } ;
struct TYPE_2__ {unsigned int (* get ) (unsigned int) ;int flags; } ;

/* Variables and functions */
 int CPUFREQ_CONST_LOOPS ; 
 int /*<<< orphan*/  cpufreq_cpu_data ; 
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_out_of_sync (unsigned int,unsigned int,unsigned int) ; 
 struct cpufreq_policy* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 unsigned int stub1 (unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int __cpufreq_get(unsigned int cpu)
{
	struct cpufreq_policy *policy = per_cpu(cpufreq_cpu_data, cpu);
	unsigned int ret_freq = 0;

	if (!cpufreq_driver->get)
		return ret_freq;

	ret_freq = cpufreq_driver->get(cpu);

	if (ret_freq && policy->cur &&
		!(cpufreq_driver->flags & CPUFREQ_CONST_LOOPS)) {
		/* verify no discrepancy between actual and
					saved value exists */
		if (unlikely(ret_freq != policy->cur)) {
			cpufreq_out_of_sync(cpu, policy->cur, ret_freq);
			schedule_work(&policy->update);
		}
	}

	return ret_freq;
}