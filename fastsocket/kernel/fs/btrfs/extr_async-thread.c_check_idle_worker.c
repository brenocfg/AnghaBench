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
struct btrfs_worker_thread {int idle; TYPE_1__* workers; int /*<<< orphan*/  worker_list; int /*<<< orphan*/  num_pending; } ;
struct TYPE_2__ {int idle_thresh; int /*<<< orphan*/  lock; int /*<<< orphan*/  idle_list; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void check_idle_worker(struct btrfs_worker_thread *worker)
{
	if (!worker->idle && atomic_read(&worker->num_pending) <
	    worker->workers->idle_thresh / 2) {
		unsigned long flags;
		spin_lock_irqsave(&worker->workers->lock, flags);
		worker->idle = 1;

		/* the list may be empty if the worker is just starting */
		if (!list_empty(&worker->worker_list)) {
			list_move(&worker->worker_list,
				 &worker->workers->idle_list);
		}
		spin_unlock_irqrestore(&worker->workers->lock, flags);
	}
}