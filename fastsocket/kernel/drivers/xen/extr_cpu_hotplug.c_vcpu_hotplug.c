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
 int /*<<< orphan*/  cpu_down (unsigned int) ; 
 int /*<<< orphan*/  cpu_possible (unsigned int) ; 
 int /*<<< orphan*/  disable_hotplug_cpu (unsigned int) ; 
 int /*<<< orphan*/  enable_hotplug_cpu (unsigned int) ; 
 int vcpu_online (unsigned int) ; 

__attribute__((used)) static void vcpu_hotplug(unsigned int cpu)
{
	if (!cpu_possible(cpu))
		return;

	switch (vcpu_online(cpu)) {
	case 1:
		enable_hotplug_cpu(cpu);
		break;
	case 0:
		(void)cpu_down(cpu);
		disable_hotplug_cpu(cpu);
		break;
	default:
		break;
	}
}