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
struct notifier_block {int dummy; } ;
struct TYPE_2__ {unsigned long min_freq; unsigned long max_freq; } ;
struct cpufreq_policy {TYPE_1__ cpuinfo; } ;

/* Variables and functions */
 unsigned long CPUFREQ_ADJUST ; 
 scalar_t__ clamped ; 
 int /*<<< orphan*/  cpufreq_verify_within_limits (struct cpufreq_policy*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int clamp_notifier_call(struct notifier_block *self,
			       unsigned long event, void *data)
{
	struct cpufreq_policy *p = data;
	unsigned long max_freq;

	if (event != CPUFREQ_ADJUST)
		return 0;

	max_freq = clamped ? (p->cpuinfo.min_freq) : (p->cpuinfo.max_freq);
	cpufreq_verify_within_limits(p, 0, max_freq);

	return 0;
}