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
struct kobject {int dummy; } ;
struct freq_attr {int /*<<< orphan*/  (* store ) (struct cpufreq_policy*,char const*,size_t) ;} ;
struct cpufreq_policy {int /*<<< orphan*/  cpu; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 struct cpufreq_policy* cpufreq_cpu_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_cpu_put (struct cpufreq_policy*) ; 
 scalar_t__ lock_policy_rwsem_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cpufreq_policy*,char const*,size_t) ; 
 struct freq_attr* to_attr (struct attribute*) ; 
 struct cpufreq_policy* to_policy (struct kobject*) ; 
 int /*<<< orphan*/  unlock_policy_rwsem_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t store(struct kobject *kobj, struct attribute *attr,
		     const char *buf, size_t count)
{
	struct cpufreq_policy *policy = to_policy(kobj);
	struct freq_attr *fattr = to_attr(attr);
	ssize_t ret = -EINVAL;
	policy = cpufreq_cpu_get(policy->cpu);
	if (!policy)
		goto no_policy;

	if (lock_policy_rwsem_write(policy->cpu) < 0)
		goto fail;

	if (fattr->store)
		ret = fattr->store(policy, buf, count);
	else
		ret = -EIO;

	unlock_policy_rwsem_write(policy->cpu);
fail:
	cpufreq_cpu_put(policy);
no_policy:
	return ret;
}