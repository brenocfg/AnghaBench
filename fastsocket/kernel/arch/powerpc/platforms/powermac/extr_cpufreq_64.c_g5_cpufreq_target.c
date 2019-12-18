#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpufreq_policy {int dummy; } ;
struct cpufreq_freqs {scalar_t__ cpu; int /*<<< orphan*/  new; int /*<<< orphan*/  old; } ;
struct TYPE_3__ {int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_POSTCHANGE ; 
 int /*<<< orphan*/  CPUFREQ_PRECHANGE ; 
 int EINVAL ; 
 scalar_t__ cpufreq_frequency_table_target (struct cpufreq_policy*,TYPE_1__*,unsigned int,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  cpufreq_notify_transition (struct cpufreq_freqs*,int /*<<< orphan*/ ) ; 
 TYPE_1__* g5_cpu_freqs ; 
 unsigned int g5_pmode_cur ; 
 int g5_switch_freq (unsigned int) ; 
 int /*<<< orphan*/  g5_switch_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int g5_cpufreq_target(struct cpufreq_policy *policy,
	unsigned int target_freq, unsigned int relation)
{
	unsigned int newstate = 0;
	struct cpufreq_freqs freqs;
	int rc;

	if (cpufreq_frequency_table_target(policy, g5_cpu_freqs,
			target_freq, relation, &newstate))
		return -EINVAL;

	if (g5_pmode_cur == newstate)
		return 0;

	mutex_lock(&g5_switch_mutex);

	freqs.old = g5_cpu_freqs[g5_pmode_cur].frequency;
	freqs.new = g5_cpu_freqs[newstate].frequency;
	freqs.cpu = 0;

	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);
	rc = g5_switch_freq(newstate);
	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);

	mutex_unlock(&g5_switch_mutex);

	return rc;
}