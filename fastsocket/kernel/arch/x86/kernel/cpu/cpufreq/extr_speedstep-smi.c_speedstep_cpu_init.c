#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  transition_latency; } ;
struct cpufreq_policy {scalar_t__ cpu; unsigned int cur; TYPE_1__ cpuinfo; } ;
struct TYPE_6__ {unsigned int frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_ETERNAL ; 
 int EINVAL ; 
 int ENODEV ; 
 size_t SPEEDSTEP_HIGH ; 
 size_t SPEEDSTEP_LOW ; 
 int cpufreq_frequency_table_cpuinfo (struct cpufreq_policy*,TYPE_2__*) ; 
 int /*<<< orphan*/  cpufreq_frequency_table_get_attr (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 TYPE_2__* speedstep_freqs ; 
 int speedstep_get_freqs (int /*<<< orphan*/ ,unsigned int*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int speedstep_get_state () ; 
 int /*<<< orphan*/  speedstep_processor ; 
 int /*<<< orphan*/  speedstep_set_state ; 
 int speedstep_smi_get_freqs (unsigned int*,unsigned int*) ; 
 int speedstep_smi_ownership () ; 

__attribute__((used)) static int speedstep_cpu_init(struct cpufreq_policy *policy)
{
	int result;
	unsigned int speed, state;
	unsigned int *low, *high;

	/* capability check */
	if (policy->cpu != 0)
		return -ENODEV;

	result = speedstep_smi_ownership();
	if (result) {
		dprintk("fails in aquiring ownership of a SMI interface.\n");
		return -EINVAL;
	}

	/* detect low and high frequency */
	low = &speedstep_freqs[SPEEDSTEP_LOW].frequency;
	high = &speedstep_freqs[SPEEDSTEP_HIGH].frequency;

	result = speedstep_smi_get_freqs(low, high);
	if (result) {
		/* fall back to speedstep_lib.c dection mechanism:
		 * try both states out */
		dprintk("could not detect low and high frequencies "
				"by SMI call.\n");
		result = speedstep_get_freqs(speedstep_processor,
				low, high,
				NULL,
				&speedstep_set_state);

		if (result) {
			dprintk("could not detect two different speeds"
					" -- aborting.\n");
			return result;
		} else
			dprintk("workaround worked.\n");
	}

	/* get current speed setting */
	state = speedstep_get_state();
	speed = speedstep_freqs[state].frequency;

	dprintk("currently at %s speed setting - %i MHz\n",
		(speed == speedstep_freqs[SPEEDSTEP_LOW].frequency)
		? "low" : "high",
		(speed / 1000));

	/* cpuinfo and default policy values */
	policy->cpuinfo.transition_latency = CPUFREQ_ETERNAL;
	policy->cur = speed;

	result = cpufreq_frequency_table_cpuinfo(policy, speedstep_freqs);
	if (result)
		return result;

	cpufreq_frequency_table_get_attr(speedstep_freqs, policy->cpu);

	return 0;
}