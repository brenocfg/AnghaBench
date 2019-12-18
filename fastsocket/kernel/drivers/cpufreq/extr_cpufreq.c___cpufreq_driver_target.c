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
struct TYPE_2__ {int (* target ) (struct cpufreq_policy*,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ cpu_online (int /*<<< orphan*/ ) ; 
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int stub1 (struct cpufreq_policy*,unsigned int,unsigned int) ; 

int __cpufreq_driver_target(struct cpufreq_policy *policy,
			    unsigned int target_freq,
			    unsigned int relation)
{
	int retval = -EINVAL;

	dprintk("target for CPU %u: %u kHz, relation %u\n", policy->cpu,
		target_freq, relation);
	if (cpu_online(policy->cpu) && cpufreq_driver->target)
		retval = cpufreq_driver->target(policy, target_freq, relation);

	return retval;
}