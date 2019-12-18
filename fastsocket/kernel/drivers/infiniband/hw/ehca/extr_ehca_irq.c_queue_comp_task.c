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
struct ehca_cq {int dummy; } ;
struct ehca_cpu_comp_task {int cq_jobs; int /*<<< orphan*/  task_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpu_comp_tasks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __queue_comp_task (struct ehca_cq*,struct ehca_cpu_comp_task*) ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 int find_next_online_cpu (TYPE_1__*) ; 
 struct ehca_cpu_comp_task* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pool ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void queue_comp_task(struct ehca_cq *__cq)
{
	int cpu_id;
	struct ehca_cpu_comp_task *cct;
	int cq_jobs;
	unsigned long flags;

	cpu_id = find_next_online_cpu(pool);
	BUG_ON(!cpu_online(cpu_id));

	cct = per_cpu_ptr(pool->cpu_comp_tasks, cpu_id);
	BUG_ON(!cct);

	spin_lock_irqsave(&cct->task_lock, flags);
	cq_jobs = cct->cq_jobs;
	spin_unlock_irqrestore(&cct->task_lock, flags);
	if (cq_jobs > 0) {
		cpu_id = find_next_online_cpu(pool);
		cct = per_cpu_ptr(pool->cpu_comp_tasks, cpu_id);
		BUG_ON(!cct);
	}

	__queue_comp_task(__cq, cct);
}