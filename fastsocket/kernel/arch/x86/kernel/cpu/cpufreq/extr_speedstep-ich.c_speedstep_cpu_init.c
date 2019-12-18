#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct get_freqs {int ret; struct cpufreq_policy* policy; } ;
struct cpufreq_policy {unsigned int cur; int /*<<< orphan*/  cpu; int /*<<< orphan*/  cpus; } ;
struct TYPE_4__ {unsigned int frequency; } ;

/* Variables and functions */
 int EIO ; 
 size_t SPEEDSTEP_LOW ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpu_sibling_mask (int /*<<< orphan*/ ) ; 
 int cpufreq_frequency_table_cpuinfo (struct cpufreq_policy*,TYPE_1__*) ; 
 int /*<<< orphan*/  cpufreq_frequency_table_get_attr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned int cpumask_any_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  get_freqs_on_cpu ; 
 int /*<<< orphan*/  smp_call_function_single (unsigned int,int /*<<< orphan*/ ,struct get_freqs*,int) ; 
 TYPE_1__* speedstep_freqs ; 
 unsigned int speedstep_get (unsigned int) ; 

__attribute__((used)) static int speedstep_cpu_init(struct cpufreq_policy *policy)
{
	int result;
	unsigned int policy_cpu, speed;
	struct get_freqs gf;

	/* only run on CPU to be set, or on its sibling */
#ifdef CONFIG_SMP
	cpumask_copy(policy->cpus, cpu_sibling_mask(policy->cpu));
#endif
	policy_cpu = cpumask_any_and(policy->cpus, cpu_online_mask);

	/* detect low and high frequency and transition latency */
	gf.policy = policy;
	smp_call_function_single(policy_cpu, get_freqs_on_cpu, &gf, 1);
	if (gf.ret)
		return gf.ret;

	/* get current speed setting */
	speed = speedstep_get(policy_cpu);
	if (!speed)
		return -EIO;

	dprintk("currently at %s speed setting - %i MHz\n",
		(speed == speedstep_freqs[SPEEDSTEP_LOW].frequency)
		? "low" : "high",
		(speed / 1000));

	/* cpuinfo and default policy values */
	policy->cur = speed;

	result = cpufreq_frequency_table_cpuinfo(policy, speedstep_freqs);
	if (result)
		return result;

	cpufreq_frequency_table_get_attr(speedstep_freqs, policy->cpu);

	return 0;
}