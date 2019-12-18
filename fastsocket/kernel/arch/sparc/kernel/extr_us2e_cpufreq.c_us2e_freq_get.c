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
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_3__ {int /*<<< orphan*/  cpus_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  HBIRD_ESTAR_MODE_ADDR ; 
 int /*<<< orphan*/  cpu_online (unsigned int) ; 
 int /*<<< orphan*/  cpumask_of_cpu (unsigned int) ; 
 TYPE_1__* current ; 
 unsigned long estar_to_divisor (unsigned long) ; 
 unsigned long read_hbreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpus_allowed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sparc64_get_clock_tick (unsigned int) ; 

__attribute__((used)) static unsigned int us2e_freq_get(unsigned int cpu)
{
	cpumask_t cpus_allowed;
	unsigned long clock_tick, estar;

	if (!cpu_online(cpu))
		return 0;

	cpus_allowed = current->cpus_allowed;
	set_cpus_allowed(current, cpumask_of_cpu(cpu));

	clock_tick = sparc64_get_clock_tick(cpu) / 1000;
	estar = read_hbreg(HBIRD_ESTAR_MODE_ADDR);

	set_cpus_allowed(current, cpus_allowed);

	return clock_tick / estar_to_divisor(estar);
}