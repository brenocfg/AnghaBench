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

/* Variables and functions */
 int /*<<< orphan*/  cpu_active_bits ; 
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_cpumask (int /*<<< orphan*/ ) ; 

void set_cpu_active(unsigned int cpu, bool active)
{
	if (active)
		cpumask_set_cpu(cpu, to_cpumask(cpu_active_bits));
	else
		cpumask_clear_cpu(cpu, to_cpumask(cpu_active_bits));
}