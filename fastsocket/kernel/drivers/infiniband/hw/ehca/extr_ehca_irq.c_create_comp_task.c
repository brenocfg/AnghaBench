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
struct ehca_cpu_comp_task {struct task_struct* task; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  cq_list; int /*<<< orphan*/  task_lock; } ;
struct ehca_comp_pool {int /*<<< orphan*/  cpu_comp_tasks; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comp_task ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct task_struct* kthread_create (int /*<<< orphan*/ ,struct ehca_cpu_comp_task*,char*,int) ; 
 struct ehca_cpu_comp_task* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct task_struct *create_comp_task(struct ehca_comp_pool *pool,
					    int cpu)
{
	struct ehca_cpu_comp_task *cct;

	cct = per_cpu_ptr(pool->cpu_comp_tasks, cpu);
	spin_lock_init(&cct->task_lock);
	INIT_LIST_HEAD(&cct->cq_list);
	init_waitqueue_head(&cct->wait_queue);
	cct->task = kthread_create(comp_task, cct, "ehca_comp/%d", cpu);

	return cct->task;
}