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
struct btrfs_worker_thread {int /*<<< orphan*/  lock; TYPE_1__* workers; int /*<<< orphan*/  worker_list; int /*<<< orphan*/  num_pending; int /*<<< orphan*/  pending; int /*<<< orphan*/  prio_pending; int /*<<< orphan*/  working; scalar_t__ idle; } ;
struct TYPE_2__ {int num_workers; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_worker (struct btrfs_worker_thread*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int try_worker_shutdown(struct btrfs_worker_thread *worker)
{
	int freeit = 0;

	spin_lock_irq(&worker->lock);
	spin_lock(&worker->workers->lock);
	if (worker->workers->num_workers > 1 &&
	    worker->idle &&
	    !worker->working &&
	    !list_empty(&worker->worker_list) &&
	    list_empty(&worker->prio_pending) &&
	    list_empty(&worker->pending) &&
	    atomic_read(&worker->num_pending) == 0) {
		freeit = 1;
		list_del_init(&worker->worker_list);
		worker->workers->num_workers--;
	}
	spin_unlock(&worker->workers->lock);
	spin_unlock_irq(&worker->lock);

	if (freeit)
		put_worker(worker);
	return freeit;
}