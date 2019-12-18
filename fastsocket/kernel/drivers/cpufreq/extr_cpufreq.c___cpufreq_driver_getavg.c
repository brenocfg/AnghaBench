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
struct cpufreq_policy {int /*<<< orphan*/  cpu; } ;
struct TYPE_2__ {int (* getavg ) (struct cpufreq_policy*,unsigned int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ cpu_online (unsigned int) ; 
 struct cpufreq_policy* cpufreq_cpu_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_cpu_put (struct cpufreq_policy*) ; 
 TYPE_1__* cpufreq_driver ; 
 int stub1 (struct cpufreq_policy*,unsigned int) ; 

int __cpufreq_driver_getavg(struct cpufreq_policy *policy, unsigned int cpu)
{
	int ret = 0;

	policy = cpufreq_cpu_get(policy->cpu);
	if (!policy)
		return -EINVAL;

	if (cpu_online(cpu) && cpufreq_driver->getavg)
		ret = cpufreq_driver->getavg(policy, cpu);

	cpufreq_cpu_put(policy);
	return ret;
}