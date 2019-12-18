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
struct autofs_wait_queue {scalar_t__ wait_queue_token; int status; int /*<<< orphan*/  queue; int /*<<< orphan*/  wait_ctr; struct autofs_wait_queue* name; struct autofs_wait_queue* next; } ;
struct autofs_sb_info {struct autofs_wait_queue* queues; } ;
typedef  scalar_t__ autofs_wqt_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kfree (struct autofs_wait_queue*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int autofs_wait_release(struct autofs_sb_info *sbi, autofs_wqt_t wait_queue_token, int status)
{
	struct autofs_wait_queue *wq, **wql;

	for (wql = &sbi->queues; (wq = *wql) != NULL; wql = &wq->next) {
		if ( wq->wait_queue_token == wait_queue_token )
			break;
	}
	if ( !wq )
		return -EINVAL;

	*wql = wq->next;	/* Unlink from chain */
	kfree(wq->name);
	wq->name = NULL;	/* Do not wait on this queue */

	wq->status = status;

	if ( ! --wq->wait_ctr )	/* Is anyone still waiting for this guy? */
		kfree(wq);
	else
		wake_up(&wq->queue);

	return 0;
}