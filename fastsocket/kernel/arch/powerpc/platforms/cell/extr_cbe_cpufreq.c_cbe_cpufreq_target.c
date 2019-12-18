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
struct cpufreq_policy {int /*<<< orphan*/  cpu; int /*<<< orphan*/  cur; } ;
struct cpufreq_freqs {int /*<<< orphan*/  cpu; int /*<<< orphan*/  new; int /*<<< orphan*/  old; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_POSTCHANGE ; 
 int /*<<< orphan*/  CPUFREQ_PRECHANGE ; 
 TYPE_1__* cbe_freqs ; 
 int /*<<< orphan*/  cbe_switch_mutex ; 
 int /*<<< orphan*/  cpufreq_frequency_table_target (struct cpufreq_policy*,TYPE_1__*,unsigned int,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  cpufreq_notify_transition (struct cpufreq_freqs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_pmode (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int cbe_cpufreq_target(struct cpufreq_policy *policy,
			      unsigned int target_freq,
			      unsigned int relation)
{
	int rc;
	struct cpufreq_freqs freqs;
	unsigned int cbe_pmode_new;

	cpufreq_frequency_table_target(policy,
				       cbe_freqs,
				       target_freq,
				       relation,
				       &cbe_pmode_new);

	freqs.old = policy->cur;
	freqs.new = cbe_freqs[cbe_pmode_new].frequency;
	freqs.cpu = policy->cpu;

	mutex_lock(&cbe_switch_mutex);
	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);

	pr_debug("setting frequency for cpu %d to %d kHz, " \
		 "1/%d of max frequency\n",
		 policy->cpu,
		 cbe_freqs[cbe_pmode_new].frequency,
		 cbe_freqs[cbe_pmode_new].index);

	rc = set_pmode(policy->cpu, cbe_pmode_new);

	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);
	mutex_unlock(&cbe_switch_mutex);

	return rc;
}