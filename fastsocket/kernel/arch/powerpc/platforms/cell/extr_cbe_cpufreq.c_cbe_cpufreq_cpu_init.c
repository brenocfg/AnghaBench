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
typedef  int u32 ;
struct device_node {int dummy; } ;
struct TYPE_5__ {int transition_latency; } ;
struct cpufreq_policy {int cpu; int cur; int /*<<< orphan*/  cpus; TYPE_1__ cpuinfo; } ;
struct TYPE_6__ {int frequency; int index; } ;

/* Variables and functions */
 int CPUFREQ_TABLE_END ; 
 int EINVAL ; 
 int ENODEV ; 
 int cbe_cpufreq_get_pmode (int) ; 
 TYPE_2__* cbe_freqs ; 
 int /*<<< orphan*/  cbe_get_cpu_mic_tm_regs (int) ; 
 int /*<<< orphan*/  cbe_get_cpu_pmd_regs (int) ; 
 int /*<<< orphan*/  cpu_sibling_map ; 
 int cpufreq_frequency_table_cpuinfo (struct cpufreq_policy*,TYPE_2__*) ; 
 int /*<<< orphan*/  cpufreq_frequency_table_get_attr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_cpu_node (int,int /*<<< orphan*/ *) ; 
 int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int cbe_cpufreq_cpu_init(struct cpufreq_policy *policy)
{
	const u32 *max_freqp;
	u32 max_freq;
	int i, cur_pmode;
	struct device_node *cpu;

	cpu = of_get_cpu_node(policy->cpu, NULL);

	if (!cpu)
		return -ENODEV;

	pr_debug("init cpufreq on CPU %d\n", policy->cpu);

	/*
	 * Let's check we can actually get to the CELL regs
	 */
	if (!cbe_get_cpu_pmd_regs(policy->cpu) ||
	    !cbe_get_cpu_mic_tm_regs(policy->cpu)) {
		pr_info("invalid CBE regs pointers for cpufreq\n");
		return -EINVAL;
	}

	max_freqp = of_get_property(cpu, "clock-frequency", NULL);

	of_node_put(cpu);

	if (!max_freqp)
		return -EINVAL;

	/* we need the freq in kHz */
	max_freq = *max_freqp / 1000;

	pr_debug("max clock-frequency is at %u kHz\n", max_freq);
	pr_debug("initializing frequency table\n");

	/* initialize frequency table */
	for (i=0; cbe_freqs[i].frequency!=CPUFREQ_TABLE_END; i++) {
		cbe_freqs[i].frequency = max_freq / cbe_freqs[i].index;
		pr_debug("%d: %d\n", i, cbe_freqs[i].frequency);
	}

	/* if DEBUG is enabled set_pmode() measures the latency
	 * of a transition */
	policy->cpuinfo.transition_latency = 25000;

	cur_pmode = cbe_cpufreq_get_pmode(policy->cpu);
	pr_debug("current pmode is at %d\n",cur_pmode);

	policy->cur = cbe_freqs[cur_pmode].frequency;

#ifdef CONFIG_SMP
	cpumask_copy(policy->cpus, &per_cpu(cpu_sibling_map, policy->cpu));
#endif

	cpufreq_frequency_table_get_attr(cbe_freqs, policy->cpu);

	/* this ensures that policy->cpuinfo_min
	 * and policy->cpuinfo_max are set correctly */
	return cpufreq_frequency_table_cpuinfo(policy, cbe_freqs);
}