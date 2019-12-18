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
struct cpufreq_policy {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_frequency_table_put_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 scalar_t__ sdcasr_mapbase ; 
 scalar_t__ sdcpwr_mapbase ; 

__attribute__((used)) static int pas_cpufreq_cpu_exit(struct cpufreq_policy *policy)
{
	if (sdcasr_mapbase)
		iounmap(sdcasr_mapbase);
	if (sdcpwr_mapbase)
		iounmap(sdcpwr_mapbase);

	cpufreq_frequency_table_put_attr(policy->cpu);
	return 0;
}