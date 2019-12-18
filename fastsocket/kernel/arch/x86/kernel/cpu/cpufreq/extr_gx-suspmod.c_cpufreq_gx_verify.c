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
typedef  int /*<<< orphan*/  u8 ;
struct cpufreq_policy {unsigned int min; unsigned int max; scalar_t__ cpu; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpufreq_verify_within_limits (struct cpufreq_policy*,unsigned int,unsigned int) ; 
 unsigned int gx_validate_speed (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int max_duration ; 
 unsigned int stock_freq ; 

__attribute__((used)) static int cpufreq_gx_verify(struct cpufreq_policy *policy)
{
	unsigned int tmp_freq = 0;
	u8 tmp1, tmp2;

	if (!stock_freq || !policy)
		return -EINVAL;

	policy->cpu = 0;
	cpufreq_verify_within_limits(policy, (stock_freq / max_duration),
			stock_freq);

	/* it needs to be assured that at least one supported frequency is
	 * within policy->min and policy->max. If it is not, policy->max
	 * needs to be increased until one freuqency is supported.
	 * policy->min may not be decreased, though. This way we guarantee a
	 * specific processing capacity.
	 */
	tmp_freq = gx_validate_speed(policy->min, &tmp1, &tmp2);
	if (tmp_freq < policy->min)
		tmp_freq += stock_freq / max_duration;
	policy->min = tmp_freq;
	if (policy->min > policy->max)
		policy->max = tmp_freq;
	tmp_freq = gx_validate_speed(policy->max, &tmp1, &tmp2);
	if (tmp_freq > policy->max)
		tmp_freq -= stock_freq / max_duration;
	policy->max = tmp_freq;
	if (policy->max < policy->min)
		policy->max = policy->min;
	cpufreq_verify_within_limits(policy, (stock_freq / max_duration),
			stock_freq);

	return 0;
}