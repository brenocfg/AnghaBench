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
struct cpufreq_freqs {unsigned long old; unsigned long new; unsigned int cpu; } ;
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_3__ {int /*<<< orphan*/  cpus_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_POSTCHANGE ; 
 int /*<<< orphan*/  CPUFREQ_PRECHANGE ; 
 int /*<<< orphan*/  HBIRD_ESTAR_MODE_ADDR ; 
 int /*<<< orphan*/  cpu_online (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_notify_transition (struct cpufreq_freqs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of_cpu (unsigned int) ; 
 TYPE_1__* current ; 
 unsigned long estar_to_divisor (unsigned long) ; 
 unsigned long index_to_divisor (unsigned int) ; 
 unsigned long index_to_estar_mode (unsigned int) ; 
 unsigned long read_hbreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpus_allowed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sparc64_get_clock_tick (unsigned int) ; 
 int /*<<< orphan*/  us2e_transition (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static void us2e_set_cpu_divider_index(unsigned int cpu, unsigned int index)
{
	unsigned long new_bits, new_freq;
	unsigned long clock_tick, divisor, old_divisor, estar;
	cpumask_t cpus_allowed;
	struct cpufreq_freqs freqs;

	if (!cpu_online(cpu))
		return;

	cpus_allowed = current->cpus_allowed;
	set_cpus_allowed(current, cpumask_of_cpu(cpu));

	new_freq = clock_tick = sparc64_get_clock_tick(cpu) / 1000;
	new_bits = index_to_estar_mode(index);
	divisor = index_to_divisor(index);
	new_freq /= divisor;

	estar = read_hbreg(HBIRD_ESTAR_MODE_ADDR);

	old_divisor = estar_to_divisor(estar);

	freqs.old = clock_tick / old_divisor;
	freqs.new = new_freq;
	freqs.cpu = cpu;
	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);

	if (old_divisor != divisor)
		us2e_transition(estar, new_bits, clock_tick * 1000,
				old_divisor, divisor);

	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);

	set_cpus_allowed(current, cpus_allowed);
}