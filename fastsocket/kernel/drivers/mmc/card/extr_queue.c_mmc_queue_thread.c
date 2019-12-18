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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {int dummy; } ;
struct mmc_queue {int /*<<< orphan*/  thread_sem; int /*<<< orphan*/  (* issue_fn ) (struct mmc_queue*,struct request*) ;struct request* req; struct request_queue* queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_MEMALLOC ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 struct request* blk_fetch_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_plugged (struct request_queue*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mmc_queue*,struct request*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mmc_queue_thread(void *d)
{
	struct mmc_queue *mq = d;
	struct request_queue *q = mq->queue;

	current->flags |= PF_MEMALLOC;

	down(&mq->thread_sem);
	do {
		struct request *req = NULL;

		spin_lock_irq(q->queue_lock);
		set_current_state(TASK_INTERRUPTIBLE);
		if (!blk_queue_plugged(q))
			req = blk_fetch_request(q);
		mq->req = req;
		spin_unlock_irq(q->queue_lock);

		if (!req) {
			if (kthread_should_stop()) {
				set_current_state(TASK_RUNNING);
				break;
			}
			up(&mq->thread_sem);
			schedule();
			down(&mq->thread_sem);
			continue;
		}
		set_current_state(TASK_RUNNING);

		mq->issue_fn(mq, req);
	} while (1);
	up(&mq->thread_sem);

	return 0;
}