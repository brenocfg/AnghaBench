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
struct cpufreq_freqs {unsigned long new; unsigned int cpu; int /*<<< orphan*/  old; } ;
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_3__ {int /*<<< orphan*/  cpus_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CPUFREQ_POSTCHANGE ; 
 int /*<<< orphan*/  CPUFREQ_PRECHANGE ; 
 unsigned long SAFARI_CFG_DIV_1 ; 
 unsigned long SAFARI_CFG_DIV_2 ; 
 unsigned long SAFARI_CFG_DIV_32 ; 
 unsigned long SAFARI_CFG_DIV_MASK ; 
 int /*<<< orphan*/  cpu_online (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_notify_transition (struct cpufreq_freqs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of_cpu (unsigned int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  get_current_freq (unsigned int,unsigned long) ; 
 unsigned long read_safari_cfg () ; 
 int /*<<< orphan*/  set_cpus_allowed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sparc64_get_clock_tick (unsigned int) ; 
 int /*<<< orphan*/  write_safari_cfg (unsigned long) ; 

__attribute__((used)) static void us3_set_cpu_divider_index(unsigned int cpu, unsigned int index)
{
	unsigned long new_bits, new_freq, reg;
	cpumask_t cpus_allowed;
	struct cpufreq_freqs freqs;

	if (!cpu_online(cpu))
		return;

	cpus_allowed = current->cpus_allowed;
	set_cpus_allowed(current, cpumask_of_cpu(cpu));

	new_freq = sparc64_get_clock_tick(cpu) / 1000;
	switch (index) {
	case 0:
		new_bits = SAFARI_CFG_DIV_1;
		new_freq /= 1;
		break;
	case 1:
		new_bits = SAFARI_CFG_DIV_2;
		new_freq /= 2;
		break;
	case 2:
		new_bits = SAFARI_CFG_DIV_32;
		new_freq /= 32;
		break;

	default:
		BUG();
	};

	reg = read_safari_cfg();

	freqs.old = get_current_freq(cpu, reg);
	freqs.new = new_freq;
	freqs.cpu = cpu;
	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);

	reg &= ~SAFARI_CFG_DIV_MASK;
	reg |= new_bits;
	write_safari_cfg(reg);

	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);

	set_cpus_allowed(current, cpus_allowed);
}