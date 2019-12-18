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
struct list_head {int dummy; } ;
struct btrfs_worker_thread {scalar_t__ working; int /*<<< orphan*/  lock; int /*<<< orphan*/  prio_pending; int /*<<< orphan*/  pending; int /*<<< orphan*/  workers; int /*<<< orphan*/  num_pending; } ;
struct btrfs_work {int /*<<< orphan*/  (* func ) (struct btrfs_work*) ;struct btrfs_worker_thread* worker; int /*<<< orphan*/  flags; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  WORK_QUEUED_BIT ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_idle_worker (struct btrfs_worker_thread*) ; 
 int /*<<< orphan*/  check_pending_worker_creates (struct btrfs_worker_thread*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ freezing (int /*<<< orphan*/ ) ; 
 struct btrfs_work* get_next_work (struct btrfs_worker_thread*,struct list_head*,struct list_head*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_ordered_completions (int /*<<< orphan*/ ,struct btrfs_work*) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct btrfs_work*) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 scalar_t__ try_worker_shutdown (struct btrfs_worker_thread*) ; 

__attribute__((used)) static int worker_loop(void *arg)
{
	struct btrfs_worker_thread *worker = arg;
	struct list_head head;
	struct list_head prio_head;
	struct btrfs_work *work;

	INIT_LIST_HEAD(&head);
	INIT_LIST_HEAD(&prio_head);

	do {
again:
		while (1) {


			work = get_next_work(worker, &prio_head, &head);
			if (!work)
				break;

			list_del(&work->list);
			clear_bit(WORK_QUEUED_BIT, &work->flags);

			work->worker = worker;

			work->func(work);

			atomic_dec(&worker->num_pending);
			/*
			 * unless this is an ordered work queue,
			 * 'work' was probably freed by func above.
			 */
			run_ordered_completions(worker->workers, work);

			check_pending_worker_creates(worker);
			cond_resched();
		}

		spin_lock_irq(&worker->lock);
		check_idle_worker(worker);

		if (freezing(current)) {
			worker->working = 0;
			spin_unlock_irq(&worker->lock);
			try_to_freeze();
		} else {
			spin_unlock_irq(&worker->lock);
			if (!kthread_should_stop()) {
				cpu_relax();
				/*
				 * we've dropped the lock, did someone else
				 * jump_in?
				 */
				smp_mb();
				if (!list_empty(&worker->pending) ||
				    !list_empty(&worker->prio_pending))
					continue;

				/*
				 * this short schedule allows more work to
				 * come in without the queue functions
				 * needing to go through wake_up_process()
				 *
				 * worker->working is still 1, so nobody
				 * is going to try and wake us up
				 */
				schedule_timeout(1);
				smp_mb();
				if (!list_empty(&worker->pending) ||
				    !list_empty(&worker->prio_pending))
					continue;

				if (kthread_should_stop())
					break;

				/* still no more work?, sleep for real */
				spin_lock_irq(&worker->lock);
				set_current_state(TASK_INTERRUPTIBLE);
				if (!list_empty(&worker->pending) ||
				    !list_empty(&worker->prio_pending)) {
					spin_unlock_irq(&worker->lock);
					set_current_state(TASK_RUNNING);
					goto again;
				}

				/*
				 * this makes sure we get a wakeup when someone
				 * adds something new to the queue
				 */
				worker->working = 0;
				spin_unlock_irq(&worker->lock);

				if (!kthread_should_stop()) {
					schedule_timeout(HZ * 120);
					if (!worker->working &&
					    try_worker_shutdown(worker)) {
						return 0;
					}
				}
			}
			__set_current_state(TASK_RUNNING);
		}
	} while (!kthread_should_stop());
	return 0;
}