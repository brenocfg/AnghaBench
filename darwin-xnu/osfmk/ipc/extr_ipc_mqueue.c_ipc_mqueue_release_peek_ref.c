#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_mqueue_t ;
struct TYPE_7__ {int /*<<< orphan*/  imq_wait_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int imq_held (TYPE_1__*) ; 
 int /*<<< orphan*/  imq_is_set (TYPE_1__*) ; 
 int /*<<< orphan*/  imq_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_release_mq (TYPE_1__*) ; 
 int /*<<< orphan*/  waitq_clear_prepost_locked (int /*<<< orphan*/ *) ; 

void ipc_mqueue_release_peek_ref(ipc_mqueue_t mq)
{
	assert(!imq_is_set(mq));
	assert(imq_held(mq));

	/*
	 * clear any preposts this mq may have generated
	 * (which would cause subsequent immediate wakeups)
	 */
	waitq_clear_prepost_locked(&mq->imq_wait_queue);

	imq_unlock(mq);

	/*
	 * release the port reference: we need to do this outside the lock
	 * because we might be holding the last port reference!
	 **/
	ip_release_mq(mq);
}