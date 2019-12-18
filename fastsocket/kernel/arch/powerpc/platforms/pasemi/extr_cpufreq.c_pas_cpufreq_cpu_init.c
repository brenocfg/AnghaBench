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
struct resource {scalar_t__ start; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  transition_latency; } ;
struct cpufreq_policy {int cpu; int cur; int /*<<< orphan*/  cpus; TYPE_1__ cpuinfo; } ;
struct TYPE_6__ {int frequency; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int CPUFREQ_TABLE_END ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ SDCASR_OFFSET ; 
 int /*<<< orphan*/  cpu_online_map ; 
 int cpufreq_frequency_table_cpuinfo (struct cpufreq_policy*,TYPE_2__*) ; 
 int /*<<< orphan*/  cpufreq_frequency_table_get_attr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_astate_freq (int /*<<< orphan*/ ) ; 
 int get_cur_astate (int) ; 
 int /*<<< orphan*/  get_gizmo_latency () ; 
 int /*<<< orphan*/  ioremap (scalar_t__,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct device_node* of_get_cpu_node (int,int /*<<< orphan*/ *) ; 
 int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 TYPE_2__* pas_freqs ; 
 unsigned long ppc_proc_freq ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  sdcasr_mapbase ; 
 int /*<<< orphan*/  sdcpwr_mapbase ; 

__attribute__((used)) static int pas_cpufreq_cpu_init(struct cpufreq_policy *policy)
{
	const u32 *max_freqp;
	u32 max_freq;
	int i, cur_astate;
	struct resource res;
	struct device_node *cpu, *dn;
	int err = -ENODEV;

	cpu = of_get_cpu_node(policy->cpu, NULL);

	if (!cpu)
		goto out;

	dn = of_find_compatible_node(NULL, NULL, "1682m-sdc");
	if (!dn)
		dn = of_find_compatible_node(NULL, NULL,
					     "pasemi,pwrficient-sdc");
	if (!dn)
		goto out;
	err = of_address_to_resource(dn, 0, &res);
	of_node_put(dn);
	if (err)
		goto out;
	sdcasr_mapbase = ioremap(res.start + SDCASR_OFFSET, 0x2000);
	if (!sdcasr_mapbase) {
		err = -EINVAL;
		goto out;
	}

	dn = of_find_compatible_node(NULL, NULL, "1682m-gizmo");
	if (!dn)
		dn = of_find_compatible_node(NULL, NULL,
					     "pasemi,pwrficient-gizmo");
	if (!dn) {
		err = -ENODEV;
		goto out_unmap_sdcasr;
	}
	err = of_address_to_resource(dn, 0, &res);
	of_node_put(dn);
	if (err)
		goto out_unmap_sdcasr;
	sdcpwr_mapbase = ioremap(res.start, 0x1000);
	if (!sdcpwr_mapbase) {
		err = -EINVAL;
		goto out_unmap_sdcasr;
	}

	pr_debug("init cpufreq on CPU %d\n", policy->cpu);

	max_freqp = of_get_property(cpu, "clock-frequency", NULL);
	if (!max_freqp) {
		err = -EINVAL;
		goto out_unmap_sdcpwr;
	}

	/* we need the freq in kHz */
	max_freq = *max_freqp / 1000;

	pr_debug("max clock-frequency is at %u kHz\n", max_freq);
	pr_debug("initializing frequency table\n");

	/* initialize frequency table */
	for (i=0; pas_freqs[i].frequency!=CPUFREQ_TABLE_END; i++) {
		pas_freqs[i].frequency = get_astate_freq(pas_freqs[i].index) * 100000;
		pr_debug("%d: %d\n", i, pas_freqs[i].frequency);
	}

	policy->cpuinfo.transition_latency = get_gizmo_latency();

	cur_astate = get_cur_astate(policy->cpu);
	pr_debug("current astate is at %d\n",cur_astate);

	policy->cur = pas_freqs[cur_astate].frequency;
	cpumask_copy(policy->cpus, &cpu_online_map);

	ppc_proc_freq = policy->cur * 1000ul;

	cpufreq_frequency_table_get_attr(pas_freqs, policy->cpu);

	/* this ensures that policy->cpuinfo_min and policy->cpuinfo_max
	 * are set correctly
	 */
	return cpufreq_frequency_table_cpuinfo(policy, pas_freqs);

out_unmap_sdcpwr:
	iounmap(sdcpwr_mapbase);

out_unmap_sdcasr:
	iounmap(sdcasr_mapbase);
out:
	return err;
}