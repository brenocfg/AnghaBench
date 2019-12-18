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
struct btrfs_worker_thread {int working; int /*<<< orphan*/  lock; int /*<<< orphan*/  task; TYPE_1__* workers; int /*<<< orphan*/  worker_list; scalar_t__ idle; int /*<<< orphan*/  num_pending; int /*<<< orphan*/  pending; int /*<<< orphan*/  prio_pending; } ;
struct btrfs_work {int /*<<< orphan*/  list; int /*<<< orphan*/  flags; struct btrfs_worker_thread* worker; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  worker_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORK_HIGH_PRIO_BIT ; 
 int /*<<< orphan*/  WORK_QUEUED_BIT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void btrfs_requeue_work(struct btrfs_work *work)
{
	struct btrfs_worker_thread *worker = work->worker;
	unsigned long flags;
	int wake = 0;

	if (test_and_set_bit(WORK_QUEUED_BIT, &work->flags))
		return;

	spin_lock_irqsave(&worker->lock, flags);
	if (test_bit(WORK_HIGH_PRIO_BIT, &work->flags))
		list_add_tail(&work->list, &worker->prio_pending);
	else
		list_add_tail(&work->list, &worker->pending);
	atomic_inc(&worker->num_pending);

	/* by definition we're busy, take ourselves off the idle
	 * list
	 */
	if (worker->idle) {
		spin_lock(&worker->workers->lock);
		worker->idle = 0;
		list_move_tail(&worker->worker_list,
			      &worker->workers->worker_list);
		spin_unlock(&worker->workers->lock);
	}
	if (!worker->working) {
		wake = 1;
		worker->working = 1;
	}

	if (wake)
		wake_up_process(worker->task);
	spin_unlock_irqrestore(&worker->lock, flags);
}