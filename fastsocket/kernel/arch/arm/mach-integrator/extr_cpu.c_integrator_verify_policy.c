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
struct icst525_vco {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_freq; int /*<<< orphan*/  min_freq; } ;
struct cpufreq_policy {TYPE_1__ cpuinfo; void* min; void* max; } ;

/* Variables and functions */
 int /*<<< orphan*/  cclk_params ; 
 int /*<<< orphan*/  cpufreq_verify_within_limits (struct cpufreq_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* icst525_khz (int /*<<< orphan*/ *,struct icst525_vco) ; 
 struct icst525_vco icst525_khz_to_vco (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int integrator_verify_policy(struct cpufreq_policy *policy)
{
	struct icst525_vco vco;

	cpufreq_verify_within_limits(policy, 
				     policy->cpuinfo.min_freq, 
				     policy->cpuinfo.max_freq);

	vco = icst525_khz_to_vco(&cclk_params, policy->max);
	policy->max = icst525_khz(&cclk_params, vco);

	vco = icst525_khz_to_vco(&cclk_params, policy->min);
	policy->min = icst525_khz(&cclk_params, vco);

	cpufreq_verify_within_limits(policy, 
				     policy->cpuinfo.min_freq, 
				     policy->cpuinfo.max_freq);

	return 0;
}