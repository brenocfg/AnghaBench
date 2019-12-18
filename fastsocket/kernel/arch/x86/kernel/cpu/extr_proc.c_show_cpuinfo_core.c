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
struct seq_file {int dummy; } ;
struct cpuinfo_x86 {int x86_max_cores; int /*<<< orphan*/  initial_apicid; int /*<<< orphan*/  apicid; int /*<<< orphan*/  booted_cores; int /*<<< orphan*/  cpu_core_id; int /*<<< orphan*/  phys_proc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_core_mask (unsigned int) ; 
 int /*<<< orphan*/  cpumask_weight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int smp_num_siblings ; 

__attribute__((used)) static void show_cpuinfo_core(struct seq_file *m, struct cpuinfo_x86 *c,
			      unsigned int cpu)
{
#ifdef CONFIG_SMP
	if (c->x86_max_cores * smp_num_siblings > 1) {
		seq_printf(m, "physical id\t: %d\n", c->phys_proc_id);
		seq_printf(m, "siblings\t: %d\n",
			   cpumask_weight(cpu_core_mask(cpu)));
		seq_printf(m, "core id\t\t: %d\n", c->cpu_core_id);
		seq_printf(m, "cpu cores\t: %d\n", c->booted_cores);
		seq_printf(m, "apicid\t\t: %d\n", c->apicid);
		seq_printf(m, "initial apicid\t: %d\n", c->initial_apicid);
	}
#endif
}