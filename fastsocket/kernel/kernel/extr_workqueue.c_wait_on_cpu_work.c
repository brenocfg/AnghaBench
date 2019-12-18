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
struct wq_barrier {int /*<<< orphan*/  done; } ;
struct work_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct cpu_workqueue_struct {int /*<<< orphan*/  lock; TYPE_1__ worklist; struct work_struct* current_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  insert_wq_barrier (struct cpu_workqueue_struct*,struct wq_barrier*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wait_on_cpu_work(struct cpu_workqueue_struct *cwq,
				struct work_struct *work)
{
	struct wq_barrier barr;
	int running = 0;

	spin_lock_irq(&cwq->lock);
	if (unlikely(cwq->current_work == work)) {
		insert_wq_barrier(cwq, &barr, cwq->worklist.next);
		running = 1;
	}
	spin_unlock_irq(&cwq->lock);

	if (unlikely(running))
		wait_for_completion(&barr.done);
}