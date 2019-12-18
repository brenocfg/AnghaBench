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
struct mask_info {struct mask_info* next; int /*<<< orphan*/  mask; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 scalar_t__ cpu_isset (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of_cpu (unsigned int) ; 
 int /*<<< orphan*/  cpus_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ cpus_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_has_topology ; 
 int /*<<< orphan*/  topology_enabled ; 

__attribute__((used)) static cpumask_t cpu_group_map(struct mask_info *info, unsigned int cpu)
{
	cpumask_t mask;

	cpus_clear(mask);
	if (!topology_enabled || !machine_has_topology)
		return cpumask_of_cpu(cpu);
	while (info) {
		if (cpu_isset(cpu, info->mask)) {
			mask = info->mask;
			break;
		}
		info = info->next;
	}
	if (cpus_empty(mask))
		mask = cpumask_of_cpu(cpu);
	return mask;
}