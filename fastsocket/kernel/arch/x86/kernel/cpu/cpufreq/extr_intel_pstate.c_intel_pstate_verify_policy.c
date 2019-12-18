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
struct TYPE_2__ {int /*<<< orphan*/  max_freq; int /*<<< orphan*/  min_freq; } ;
struct cpufreq_policy {scalar_t__ policy; TYPE_1__ cpuinfo; } ;

/* Variables and functions */
 scalar_t__ CPUFREQ_POLICY_PERFORMANCE ; 
 scalar_t__ CPUFREQ_POLICY_POWERSAVE ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpufreq_verify_within_limits (struct cpufreq_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pstate_verify_policy(struct cpufreq_policy *policy)
{
	cpufreq_verify_within_limits(policy,
				policy->cpuinfo.min_freq,
				policy->cpuinfo.max_freq);

	if ((policy->policy != CPUFREQ_POLICY_POWERSAVE) &&
		(policy->policy != CPUFREQ_POLICY_PERFORMANCE))
		return -EINVAL;

	return 0;
}