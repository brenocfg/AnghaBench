#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct waitq {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* ipc_mqueue_t ;
struct TYPE_4__ {struct waitq imq_wait_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imq_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  waitq_unlink_all_unlock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_valid (struct waitq*) ; 

void
ipc_mqueue_remove_from_all(ipc_mqueue_t	mqueue)
{
	struct waitq *mq_waitq = &mqueue->imq_wait_queue;
	kern_return_t kr;

	imq_lock(mqueue);

	assert(waitq_valid(mq_waitq));
	kr = waitq_unlink_all_unlock(mq_waitq);
	/* mqueue unlocked and set links deallocated */
}