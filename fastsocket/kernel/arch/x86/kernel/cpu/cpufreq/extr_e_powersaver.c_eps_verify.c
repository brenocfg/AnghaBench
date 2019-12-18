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
struct TYPE_2__ {int /*<<< orphan*/ * freq_table; } ;

/* Variables and functions */
 int cpufreq_frequency_table_verify (struct cpufreq_policy*,int /*<<< orphan*/ *) ; 
 TYPE_1__** eps_cpu ; 

__attribute__((used)) static int eps_verify(struct cpufreq_policy *policy)
{
	return cpufreq_frequency_table_verify(policy,
			&eps_cpu[policy->cpu]->freq_table[0]);
}