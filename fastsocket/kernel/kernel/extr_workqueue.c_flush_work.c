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
struct list_head {int /*<<< orphan*/  next; } ;
struct work_struct {struct list_head entry; } ;
struct cpu_workqueue_struct {int /*<<< orphan*/  lock; struct list_head worklist; struct work_struct* current_work; TYPE_1__* wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  lockdep_map; } ;

/* Variables and functions */
 struct cpu_workqueue_struct* get_wq_data (struct work_struct*) ; 
 int /*<<< orphan*/  insert_wq_barrier (struct cpu_workqueue_struct*,struct wq_barrier*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  lock_map_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_map_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int flush_work(struct work_struct *work)
{
	struct cpu_workqueue_struct *cwq;
	struct list_head *prev;
	struct wq_barrier barr;

	might_sleep();
	cwq = get_wq_data(work);
	if (!cwq)
		return 0;

	lock_map_acquire(&cwq->wq->lockdep_map);
	lock_map_release(&cwq->wq->lockdep_map);

	prev = NULL;
	spin_lock_irq(&cwq->lock);
	if (!list_empty(&work->entry)) {
		/*
		 * See the comment near try_to_grab_pending()->smp_rmb().
		 * If it was re-queued under us we are not going to wait.
		 */
		smp_rmb();
		if (unlikely(cwq != get_wq_data(work)))
			goto out;
		prev = &work->entry;
	} else {
		if (cwq->current_work != work)
			goto out;
		prev = &cwq->worklist;
	}
	insert_wq_barrier(cwq, &barr, prev->next);
out:
	spin_unlock_irq(&cwq->lock);
	if (!prev)
		return 0;

	wait_for_completion(&barr.done);
	return 1;
}