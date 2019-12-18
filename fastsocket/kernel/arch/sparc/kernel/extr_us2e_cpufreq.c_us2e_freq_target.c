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
struct cpufreq_policy {size_t cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/ * table; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ cpufreq_frequency_table_target (struct cpufreq_policy*,int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int*) ; 
 TYPE_1__* us2e_freq_table ; 
 int /*<<< orphan*/  us2e_set_cpu_divider_index (size_t,unsigned int) ; 

__attribute__((used)) static int us2e_freq_target(struct cpufreq_policy *policy,
			  unsigned int target_freq,
			  unsigned int relation)
{
	unsigned int new_index = 0;

	if (cpufreq_frequency_table_target(policy,
					   &us2e_freq_table[policy->cpu].table[0],
					   target_freq, relation, &new_index))
		return -EINVAL;

	us2e_set_cpu_divider_index(policy->cpu, new_index);

	return 0;
}