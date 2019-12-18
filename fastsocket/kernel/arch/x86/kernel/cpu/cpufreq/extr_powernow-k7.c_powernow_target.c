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
struct cpufreq_policy {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  change_speed (unsigned int) ; 
 scalar_t__ cpufreq_frequency_table_target (struct cpufreq_policy*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  powernow_table ; 

__attribute__((used)) static int powernow_target(struct cpufreq_policy *policy,
			    unsigned int target_freq,
			    unsigned int relation)
{
	unsigned int newstate;

	if (cpufreq_frequency_table_target(policy, powernow_table, target_freq,
				relation, &newstate))
		return -EINVAL;

	change_speed(newstate);

	return 0;
}