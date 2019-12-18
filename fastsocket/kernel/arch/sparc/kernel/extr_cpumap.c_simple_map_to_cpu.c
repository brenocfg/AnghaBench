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
 scalar_t__ cpu_online (int) ; 
 int /*<<< orphan*/  cpu_online_map ; 
 int first_cpu (int /*<<< orphan*/ ) ; 
 unsigned int num_online_cpus () ; 
 int num_possible_cpus () ; 

__attribute__((used)) static int simple_map_to_cpu(unsigned int index)
{
	int i, end, cpu_rover;

	cpu_rover = 0;
	end = index % num_online_cpus();
	for (i = 0; i < num_possible_cpus(); i++) {
		if (cpu_online(cpu_rover)) {
			if (cpu_rover >= end)
				return cpu_rover;

			cpu_rover++;
		}
	}

	/* Impossible, since num_online_cpus() <= num_possible_cpus() */
	return first_cpu(cpu_online_map);
}