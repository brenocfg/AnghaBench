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
struct TYPE_2__ {struct autofs_wait_queue* name; } ;
struct autofs_wait_queue {scalar_t__ wait_queue_token; int status; int /*<<< orphan*/  wait_ctr; int /*<<< orphan*/  queue; TYPE_1__ name; struct autofs_wait_queue* next; } ;
struct autofs_sb_info {int /*<<< orphan*/  wq_mutex; struct autofs_wait_queue* queues; } ;
typedef  scalar_t__ autofs_wqt_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kfree (struct autofs_wait_queue*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int autofs4_wait_release(struct autofs_sb_info *sbi, autofs_wqt_t wait_queue_token, int status)
{
	struct autofs_wait_queue *wq, **wql;

	mutex_lock(&sbi->wq_mutex);
	for (wql = &sbi->queues; (wq = *wql) != NULL; wql = &wq->next) {
		if (wq->wait_queue_token == wait_queue_token)
			break;
	}

	if (!wq) {
		mutex_unlock(&sbi->wq_mutex);
		return -EINVAL;
	}

	*wql = wq->next;	/* Unlink from chain */
	kfree(wq->name.name);
	wq->name.name = NULL;	/* Do not wait on this queue */
	wq->status = status;
	wake_up_interruptible(&wq->queue);
	if (!--wq->wait_ctr)
		kfree(wq);
	mutex_unlock(&sbi->wq_mutex);

	return 0;
}