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
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_HIGH ; 
 scalar_t__ cur_freq ; 
 int /*<<< orphan*/  do_set_cpu_speed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_pmu_based ; 
 scalar_t__ low_freq ; 
 int no_schedule ; 
 scalar_t__ sleep_freq ; 

__attribute__((used)) static int pmac_cpufreq_suspend(struct cpufreq_policy *policy, pm_message_t pmsg)
{
	/* Ok, this could be made a bit smarter, but let's be robust for now. We
	 * always force a speed change to high speed before sleep, to make sure
	 * we have appropriate voltage and/or bus speed for the wakeup process,
	 * and to make sure our loops_per_jiffies are "good enough", that is will
	 * not cause too short delays if we sleep in low speed and wake in high
	 * speed..
	 */
	no_schedule = 1;
	sleep_freq = cur_freq;
	if (cur_freq == low_freq && !is_pmu_based)
		do_set_cpu_speed(CPUFREQ_HIGH, 0);
	return 0;
}