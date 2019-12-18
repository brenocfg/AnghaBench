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
struct cpufreq_freqs {scalar_t__ old; scalar_t__ new; scalar_t__ cpu; } ;
struct TYPE_3__ {scalar_t__ frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_POSTCHANGE ; 
 int /*<<< orphan*/  CPUFREQ_PRECHANGE ; 
 int EINVAL ; 
 scalar_t__ cpufreq_frequency_table_target (struct cpufreq_policy*,TYPE_1__*,unsigned int,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  cpufreq_notify_transition (struct cpufreq_freqs*,int /*<<< orphan*/ ) ; 
 TYPE_1__* speedstep_freqs ; 
 size_t speedstep_get_state () ; 
 int /*<<< orphan*/  speedstep_set_state (unsigned int) ; 

__attribute__((used)) static int speedstep_target(struct cpufreq_policy *policy,
			unsigned int target_freq, unsigned int relation)
{
	unsigned int newstate = 0;
	struct cpufreq_freqs freqs;

	if (cpufreq_frequency_table_target(policy, &speedstep_freqs[0],
				target_freq, relation, &newstate))
		return -EINVAL;

	freqs.old = speedstep_freqs[speedstep_get_state()].frequency;
	freqs.new = speedstep_freqs[newstate].frequency;
	freqs.cpu = 0; /* speedstep.c is UP only driver */

	if (freqs.old == freqs.new)
		return 0;

	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);
	speedstep_set_state(newstate);
	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);

	return 0;
}