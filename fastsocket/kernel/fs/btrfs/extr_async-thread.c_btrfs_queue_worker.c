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
struct btrfs_workers {int /*<<< orphan*/  order_lock; int /*<<< orphan*/  order_list; int /*<<< orphan*/  prio_order_list; scalar_t__ ordered; } ;
struct btrfs_worker_thread {int working; int /*<<< orphan*/  lock; int /*<<< orphan*/  task; int /*<<< orphan*/  pending; int /*<<< orphan*/  prio_pending; } ;
struct btrfs_work {int /*<<< orphan*/  list; int /*<<< orphan*/  flags; int /*<<< orphan*/  order_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WORK_HIGH_PRIO_BIT ; 
 int /*<<< orphan*/  WORK_QUEUED_BIT ; 
 int /*<<< orphan*/  check_busy_worker (struct btrfs_worker_thread*) ; 
 struct btrfs_worker_thread* find_worker (struct btrfs_workers*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void btrfs_queue_worker(struct btrfs_workers *workers, struct btrfs_work *work)
{
	struct btrfs_worker_thread *worker;
	unsigned long flags;
	int wake = 0;

	/* don't requeue something already on a list */
	if (test_and_set_bit(WORK_QUEUED_BIT, &work->flags))
		return;

	worker = find_worker(workers);
	if (workers->ordered) {
		/*
		 * you're not allowed to do ordered queues from an
		 * interrupt handler
		 */
		spin_lock(&workers->order_lock);
		if (test_bit(WORK_HIGH_PRIO_BIT, &work->flags)) {
			list_add_tail(&work->order_list,
				      &workers->prio_order_list);
		} else {
			list_add_tail(&work->order_list, &workers->order_list);
		}
		spin_unlock(&workers->order_lock);
	} else {
		INIT_LIST_HEAD(&work->order_list);
	}

	spin_lock_irqsave(&worker->lock, flags);

	if (test_bit(WORK_HIGH_PRIO_BIT, &work->flags))
		list_add_tail(&work->list, &worker->prio_pending);
	else
		list_add_tail(&work->list, &worker->pending);
	check_busy_worker(worker);

	/*
	 * avoid calling into wake_up_process if this thread has already
	 * been kicked
	 */
	if (!worker->working)
		wake = 1;
	worker->working = 1;

	if (wake)
		wake_up_process(worker->task);
	spin_unlock_irqrestore(&worker->lock, flags);
}