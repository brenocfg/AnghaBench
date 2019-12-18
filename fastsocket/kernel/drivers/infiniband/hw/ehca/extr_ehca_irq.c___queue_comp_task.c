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
struct ehca_cq {scalar_t__ nr_callbacks; int /*<<< orphan*/  task_lock; int /*<<< orphan*/  entry; } ;
struct ehca_cpu_comp_task {int /*<<< orphan*/  task_lock; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  cq_jobs; int /*<<< orphan*/  cq_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __queue_comp_task(struct ehca_cq *__cq,
			      struct ehca_cpu_comp_task *cct)
{
	unsigned long flags;

	spin_lock_irqsave(&cct->task_lock, flags);
	spin_lock(&__cq->task_lock);

	if (__cq->nr_callbacks == 0) {
		__cq->nr_callbacks++;
		list_add_tail(&__cq->entry, &cct->cq_list);
		cct->cq_jobs++;
		wake_up(&cct->wait_queue);
	} else
		__cq->nr_callbacks++;

	spin_unlock(&__cq->task_lock);
	spin_unlock_irqrestore(&cct->task_lock, flags);
}