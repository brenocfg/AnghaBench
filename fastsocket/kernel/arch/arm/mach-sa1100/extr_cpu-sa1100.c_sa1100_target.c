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
struct cpufreq_policy {unsigned int max; unsigned int min; } ;
struct cpufreq_freqs {unsigned int old; unsigned int new; scalar_t__ cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_POSTCHANGE ; 
 int /*<<< orphan*/  CPUFREQ_PRECHANGE ; 
#define  CPUFREQ_RELATION_H 129 
#define  CPUFREQ_RELATION_L 128 
 unsigned int PPCR ; 
 int /*<<< orphan*/  cpufreq_notify_transition (struct cpufreq_freqs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1100_update_dram_timings (unsigned int,unsigned int) ; 
 unsigned int sa11x0_freq_to_ppcr (unsigned int) ; 
 unsigned int sa11x0_getspeed (int /*<<< orphan*/ ) ; 
 unsigned int sa11x0_ppcr_to_freq (unsigned int) ; 

__attribute__((used)) static int sa1100_target(struct cpufreq_policy *policy,
			 unsigned int target_freq,
			 unsigned int relation)
{
	unsigned int cur = sa11x0_getspeed(0);
	unsigned int new_ppcr;

	struct cpufreq_freqs freqs;
	switch(relation){
	case CPUFREQ_RELATION_L:
		new_ppcr = sa11x0_freq_to_ppcr(target_freq);
		if (sa11x0_ppcr_to_freq(new_ppcr) > policy->max)
			new_ppcr--;
		break;
	case CPUFREQ_RELATION_H:
		new_ppcr = sa11x0_freq_to_ppcr(target_freq);
		if ((sa11x0_ppcr_to_freq(new_ppcr) > target_freq) &&
		    (sa11x0_ppcr_to_freq(new_ppcr - 1) >= policy->min))
			new_ppcr--;
		break;
	}

	freqs.old = cur;
	freqs.new = sa11x0_ppcr_to_freq(new_ppcr);
	freqs.cpu = 0;

	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);

	if (freqs.new > cur)
		sa1100_update_dram_timings(cur, freqs.new);

	PPCR = new_ppcr;

	if (freqs.new < cur)
		sa1100_update_dram_timings(cur, freqs.new);

	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);

	return 0;
}