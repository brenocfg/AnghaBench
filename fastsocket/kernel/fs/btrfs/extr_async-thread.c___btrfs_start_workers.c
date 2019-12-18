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
struct btrfs_workers {scalar_t__ num_workers_starting; int /*<<< orphan*/  lock; scalar_t__ num_workers; int /*<<< orphan*/  idle_list; int /*<<< orphan*/  name; } ;
struct btrfs_worker_thread {int idle; int /*<<< orphan*/  worker_list; int /*<<< orphan*/  task; struct btrfs_workers* workers; int /*<<< orphan*/  refs; int /*<<< orphan*/  num_pending; int /*<<< orphan*/  lock; int /*<<< orphan*/  prio_pending; int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct btrfs_worker_thread*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct btrfs_worker_thread*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct btrfs_worker_thread* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  worker_loop ; 

__attribute__((used)) static int __btrfs_start_workers(struct btrfs_workers *workers)
{
	struct btrfs_worker_thread *worker;
	int ret = 0;

	worker = kzalloc(sizeof(*worker), GFP_NOFS);
	if (!worker) {
		ret = -ENOMEM;
		goto fail;
	}

	INIT_LIST_HEAD(&worker->pending);
	INIT_LIST_HEAD(&worker->prio_pending);
	INIT_LIST_HEAD(&worker->worker_list);
	spin_lock_init(&worker->lock);

	atomic_set(&worker->num_pending, 0);
	atomic_set(&worker->refs, 1);
	worker->workers = workers;
	worker->task = kthread_run(worker_loop, worker,
				   "btrfs-%s-%d", workers->name,
				   workers->num_workers + 1);
	if (IS_ERR(worker->task)) {
		ret = PTR_ERR(worker->task);
		kfree(worker);
		goto fail;
	}
	spin_lock_irq(&workers->lock);
	list_add_tail(&worker->worker_list, &workers->idle_list);
	worker->idle = 1;
	workers->num_workers++;
	workers->num_workers_starting--;
	WARN_ON(workers->num_workers_starting < 0);
	spin_unlock_irq(&workers->lock);

	return 0;
fail:
	spin_lock_irq(&workers->lock);
	workers->num_workers_starting--;
	spin_unlock_irq(&workers->lock);
	return ret;
}