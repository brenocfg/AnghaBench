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
struct task_struct {int dummy; } ;
struct ehca_cpu_comp_task {int /*<<< orphan*/  task_lock; scalar_t__ cq_jobs; struct task_struct* task; } ;
struct ehca_comp_pool {int /*<<< orphan*/  cpu_comp_tasks; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_stop (struct task_struct*) ; 
 struct ehca_cpu_comp_task* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void destroy_comp_task(struct ehca_comp_pool *pool,
			      int cpu)
{
	struct ehca_cpu_comp_task *cct;
	struct task_struct *task;
	unsigned long flags_cct;

	cct = per_cpu_ptr(pool->cpu_comp_tasks, cpu);

	spin_lock_irqsave(&cct->task_lock, flags_cct);

	task = cct->task;
	cct->task = NULL;
	cct->cq_jobs = 0;

	spin_unlock_irqrestore(&cct->task_lock, flags_cct);

	if (task)
		kthread_stop(task);
}