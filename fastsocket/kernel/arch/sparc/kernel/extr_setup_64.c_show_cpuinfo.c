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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clock_tick; } ;

/* Variables and functions */
 TYPE_1__ cpu_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcache_parity_tl1_occurred ; 
 scalar_t__ hypervisor ; 
 int /*<<< orphan*/  icache_parity_tl1_occurred ; 
 int /*<<< orphan*/  mmu_info (struct seq_file*) ; 
 int /*<<< orphan*/  ncpus_probed ; 
 int /*<<< orphan*/  num_online_cpus () ; 
 int /*<<< orphan*/  prom_version ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_bogo (struct seq_file*) ; 
 int /*<<< orphan*/  smp_info (struct seq_file*) ; 
 int /*<<< orphan*/  sparc_cpu_type ; 
 int /*<<< orphan*/  sparc_fpu_type ; 
 int /*<<< orphan*/  sparc_pmu_type ; 
 scalar_t__ tlb_type ; 

__attribute__((used)) static int show_cpuinfo(struct seq_file *m, void *__unused)
{
	seq_printf(m, 
		   "cpu\t\t: %s\n"
		   "fpu\t\t: %s\n"
		   "pmu\t\t: %s\n"
		   "prom\t\t: %s\n"
		   "type\t\t: %s\n"
		   "ncpus probed\t: %d\n"
		   "ncpus active\t: %d\n"
		   "D$ parity tl1\t: %u\n"
		   "I$ parity tl1\t: %u\n"
#ifndef CONFIG_SMP
		   "Cpu0ClkTck\t: %016lx\n"
#endif
		   ,
		   sparc_cpu_type,
		   sparc_fpu_type,
		   sparc_pmu_type,
		   prom_version,
		   ((tlb_type == hypervisor) ?
		    "sun4v" :
		    "sun4u"),
		   ncpus_probed,
		   num_online_cpus(),
		   dcache_parity_tl1_occurred,
		   icache_parity_tl1_occurred
#ifndef CONFIG_SMP
		   , cpu_data(0).clock_tick
#endif
		);
#ifdef CONFIG_SMP
	smp_bogo(m);
#endif
	mmu_info(m);
#ifdef CONFIG_SMP
	smp_info(m);
#endif
	return 0;
}