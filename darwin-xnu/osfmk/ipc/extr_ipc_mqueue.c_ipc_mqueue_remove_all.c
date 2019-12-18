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
struct waitq_set {int dummy; } ;
typedef  TYPE_1__* ipc_mqueue_t ;
struct TYPE_4__ {struct waitq_set imq_set_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imq_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  waitq_set_unlink_all_unlock (struct waitq_set*) ; 
 int /*<<< orphan*/  waitqs_is_set (struct waitq_set*) ; 

void
ipc_mqueue_remove_all(ipc_mqueue_t	mqueue)
{
	struct waitq_set *mq_setq = &mqueue->imq_set_queue;

	imq_lock(mqueue);
	assert(waitqs_is_set(mq_setq));
	waitq_set_unlink_all_unlock(mq_setq);
	/* mqueue unlocked set links deallocated */
}