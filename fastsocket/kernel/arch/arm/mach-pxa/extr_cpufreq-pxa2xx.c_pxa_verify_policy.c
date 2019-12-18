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
struct cpufreq_policy {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct cpufreq_frequency_table {int dummy; } ;
typedef  int /*<<< orphan*/  pxa_freqs_t ;

/* Variables and functions */
 int cpufreq_frequency_table_verify (struct cpufreq_policy*,struct cpufreq_frequency_table*) ; 
 int /*<<< orphan*/  find_freq_tables (struct cpufreq_frequency_table**,int /*<<< orphan*/ **) ; 
 scalar_t__ freq_debug ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa_verify_policy(struct cpufreq_policy *policy)
{
	struct cpufreq_frequency_table *pxa_freqs_table;
	pxa_freqs_t *pxa_freqs;
	int ret;

	find_freq_tables(&pxa_freqs_table, &pxa_freqs);
	ret = cpufreq_frequency_table_verify(policy, pxa_freqs_table);

	if (freq_debug)
		pr_debug("Verified CPU policy: %dKhz min to %dKhz max\n",
			 policy->min, policy->max);

	return ret;
}