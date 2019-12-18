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
struct cpumask {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_clear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear (struct cpumask*) ; 
 int /*<<< orphan*/  cpus_setall (struct cpumask) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  fastsocket_spawn_cpu ; 
 int /*<<< orphan*/  fastsocket_spawn_cpuset ; 
 int /*<<< orphan*/  sched_setaffinity (int /*<<< orphan*/ ,struct cpumask*) ; 

__attribute__((used)) static void fsocket_process_affinity_restore(int cpu)
{
	struct cpumask mask;
	
	cpumask_clear(&mask);
	cpus_setall(mask);

	sched_setaffinity(current->pid, &mask);

	if (-1 != cpu) {
		cpu_clear(cpu, fastsocket_spawn_cpuset);
		fastsocket_spawn_cpu--;
	}
}