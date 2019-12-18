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
struct cpufreq_freqs {int flags; scalar_t__ old; scalar_t__ new; } ;

/* Variables and functions */
 int CPUFREQ_CONST_LOOPS ; 
 unsigned long CPUFREQ_POSTCHANGE ; 
 unsigned long CPUFREQ_PRECHANGE ; 
 unsigned long CPUFREQ_RESUMECHANGE ; 
 unsigned long CPUFREQ_SUSPENDCHANGE ; 
 int /*<<< orphan*/  cpufreq_scale (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  l_p_j_ref ; 
 scalar_t__ l_p_j_ref_freq ; 
 int /*<<< orphan*/  loops_per_jiffy ; 

__attribute__((used)) static void adjust_jiffies(unsigned long val, struct cpufreq_freqs *ci)
{
	if (ci->flags & CPUFREQ_CONST_LOOPS)
		return;

	if (!l_p_j_ref_freq) {
		l_p_j_ref = loops_per_jiffy;
		l_p_j_ref_freq = ci->old;
		dprintk("saving %lu as reference value for loops_per_jiffy; "
			"freq is %u kHz\n", l_p_j_ref, l_p_j_ref_freq);
	}
	if ((val == CPUFREQ_PRECHANGE  && ci->old < ci->new) ||
	    (val == CPUFREQ_POSTCHANGE && ci->old > ci->new) ||
	    (val == CPUFREQ_RESUMECHANGE || val == CPUFREQ_SUSPENDCHANGE)) {
		loops_per_jiffy = cpufreq_scale(l_p_j_ref, l_p_j_ref_freq,
								ci->new);
		dprintk("scaling loops_per_jiffy to %lu "
			"for frequency %u kHz\n", loops_per_jiffy, ci->new);
	}
}