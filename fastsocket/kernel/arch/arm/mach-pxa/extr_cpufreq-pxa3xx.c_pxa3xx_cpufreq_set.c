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
struct pxa3xx_freq_info {int cpufreq_mhz; } ;
struct cpufreq_policy {scalar_t__ cpu; int cur; } ;
struct cpufreq_freqs {int old; int new; scalar_t__ cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_POSTCHANGE ; 
 int /*<<< orphan*/  CPUFREQ_PRECHANGE ; 
 int EINVAL ; 
 int /*<<< orphan*/  __update_bus_freq (struct pxa3xx_freq_info*) ; 
 int /*<<< orphan*/  __update_core_freq (struct pxa3xx_freq_info*) ; 
 scalar_t__ cpufreq_frequency_table_target (struct cpufreq_policy*,int /*<<< orphan*/ ,unsigned int,unsigned int,int*) ; 
 int /*<<< orphan*/  cpufreq_notify_transition (struct cpufreq_freqs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,char*) ; 
 struct pxa3xx_freq_info* pxa3xx_freqs ; 
 int /*<<< orphan*/  pxa3xx_freqs_table ; 

__attribute__((used)) static int pxa3xx_cpufreq_set(struct cpufreq_policy *policy,
			      unsigned int target_freq,
			      unsigned int relation)
{
	struct pxa3xx_freq_info *next;
	struct cpufreq_freqs freqs;
	unsigned long flags;
	int idx;

	if (policy->cpu != 0)
		return -EINVAL;

	/* Lookup the next frequency */
	if (cpufreq_frequency_table_target(policy, pxa3xx_freqs_table,
				target_freq, relation, &idx))
		return -EINVAL;

	next = &pxa3xx_freqs[idx];

	freqs.old = policy->cur;
	freqs.new = next->cpufreq_mhz * 1000;
	freqs.cpu = policy->cpu;

	pr_debug("CPU frequency from %d MHz to %d MHz%s\n",
			freqs.old / 1000, freqs.new / 1000,
			(freqs.old == freqs.new) ? " (skipped)" : "");

	if (freqs.old == target_freq)
		return 0;

	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);

	local_irq_save(flags);
	__update_core_freq(next);
	__update_bus_freq(next);
	local_irq_restore(flags);

	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);

	return 0;
}