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
struct TYPE_2__ {int transition_latency; } ;
struct cpufreq_policy {int /*<<< orphan*/  cpu; int /*<<< orphan*/  cur; TYPE_1__ cpuinfo; } ;

/* Variables and functions */
 int cpufreq_frequency_table_cpuinfo (struct cpufreq_policy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_frequency_table_get_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cris_freq_get_cpu_frequency (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cris_freq_table ; 

__attribute__((used)) static int cris_freq_cpu_init(struct cpufreq_policy *policy)
{
	int result;

	/* cpuinfo and default policy values */
	policy->cpuinfo.transition_latency = 1000000;	/* 1ms */
	policy->cur = cris_freq_get_cpu_frequency(0);

	result = cpufreq_frequency_table_cpuinfo(policy, cris_freq_table);
	if (result)
		return (result);

	cpufreq_frequency_table_get_attr(cris_freq_table, policy->cpu);

	return 0;
}