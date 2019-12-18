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
 int /*<<< orphan*/  arch_register_cpu (int) ; 
 int /*<<< orphan*/  cpu_present (int) ; 
 int /*<<< orphan*/  set_cpu_present (int,int) ; 

__attribute__((used)) static void enable_hotplug_cpu(int cpu)
{
	if (!cpu_present(cpu))
		arch_register_cpu(cpu);

	set_cpu_present(cpu, true);
}