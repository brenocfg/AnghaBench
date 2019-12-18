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
struct TYPE_2__ {int nr_cpus_allowed; } ;
struct task_struct {int /*<<< orphan*/  flags; TYPE_1__ rt; int /*<<< orphan*/  cpus_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_THREAD_BOUND ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpumask_of_cpu (unsigned int) ; 
 int /*<<< orphan*/  wait_task_inactive (struct task_struct*,int /*<<< orphan*/ ) ; 

void kthread_bind(struct task_struct *p, unsigned int cpu)
{
	/* Must have done schedule() in kthread() before we set_task_cpu */
	if (!wait_task_inactive(p, TASK_UNINTERRUPTIBLE)) {
		WARN_ON(1);
		return;
	}

	p->cpus_allowed = cpumask_of_cpu(cpu);
	p->rt.nr_cpus_allowed = 1;
	p->flags |= PF_THREAD_BOUND;
}