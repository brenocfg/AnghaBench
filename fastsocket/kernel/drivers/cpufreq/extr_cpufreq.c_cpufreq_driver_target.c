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
struct cpufreq_policy {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int EINVAL ; 
 int __cpufreq_driver_target (struct cpufreq_policy*,unsigned int,unsigned int) ; 
 struct cpufreq_policy* cpufreq_cpu_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_cpu_put (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  lock_policy_rwsem_write (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_policy_rwsem_write (int /*<<< orphan*/ ) ; 

int cpufreq_driver_target(struct cpufreq_policy *policy,
			  unsigned int target_freq,
			  unsigned int relation)
{
	int ret = -EINVAL;

	policy = cpufreq_cpu_get(policy->cpu);
	if (!policy)
		goto no_policy;

	if (unlikely(lock_policy_rwsem_write(policy->cpu)))
		goto fail;

	ret = __cpufreq_driver_target(policy, target_freq, relation);

	unlock_policy_rwsem_write(policy->cpu);

fail:
	cpufreq_cpu_put(policy);
no_policy:
	return ret;
}