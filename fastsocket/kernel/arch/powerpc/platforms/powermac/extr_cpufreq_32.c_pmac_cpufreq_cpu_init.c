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
struct TYPE_2__ {int /*<<< orphan*/  transition_latency; } ;
struct cpufreq_policy {scalar_t__ cpu; int /*<<< orphan*/  cur; TYPE_1__ cpuinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_ETERNAL ; 
 int ENODEV ; 
 int cpufreq_frequency_table_cpuinfo (struct cpufreq_policy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_frequency_table_get_attr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cur_freq ; 
 int /*<<< orphan*/  pmac_cpu_freqs ; 

__attribute__((used)) static int pmac_cpufreq_cpu_init(struct cpufreq_policy *policy)
{
	if (policy->cpu != 0)
		return -ENODEV;

	policy->cpuinfo.transition_latency	= CPUFREQ_ETERNAL;
	policy->cur = cur_freq;

	cpufreq_frequency_table_get_attr(pmac_cpu_freqs, policy->cpu);
	return cpufreq_frequency_table_cpuinfo(policy, pmac_cpu_freqs);
}