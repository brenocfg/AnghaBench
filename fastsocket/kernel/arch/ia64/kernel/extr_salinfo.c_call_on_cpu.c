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
 int /*<<< orphan*/  cpumask_of_cpu (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  set_cpus_allowed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void stub1 (void*) ; 

__attribute__((used)) static void
call_on_cpu(int cpu, void (*fn)(void *), void *arg)
{
	cpumask_t save_cpus_allowed = current->cpus_allowed;
	cpumask_t new_cpus_allowed = cpumask_of_cpu(cpu);
	set_cpus_allowed(current, new_cpus_allowed);
	(*fn)(arg);
	set_cpus_allowed(current, save_cpus_allowed);
}