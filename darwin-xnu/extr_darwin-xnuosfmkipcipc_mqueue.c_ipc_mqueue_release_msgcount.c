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
struct turnstile {int /*<<< orphan*/  ts_waitq; } ;
typedef  TYPE_1__* ipc_mqueue_t ;
struct TYPE_7__ {int imq_msgcount; int /*<<< orphan*/  imq_wait_queue; int /*<<< orphan*/  imq_messages; scalar_t__ imq_fullwaiters; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IPC_MQUEUE_FULL ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  THREAD_AWAKENED ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  WAITQ_PROMOTE_PRIORITY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  imq_full (TYPE_1__*) ; 
 int imq_held (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_from_mq (TYPE_1__*) ; 
 scalar_t__ ipc_kmsg_queue_empty (int /*<<< orphan*/ *) ; 
 struct turnstile* port_send_turnstile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_clear_prepost_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ waitq_wakeup64_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipc_mqueue_release_msgcount(ipc_mqueue_t port_mq, ipc_mqueue_t set_mq)
{
	struct turnstile *send_turnstile = port_send_turnstile(ip_from_mq(port_mq));
	(void)set_mq;
	assert(imq_held(port_mq));
	assert(port_mq->imq_msgcount > 1 || ipc_kmsg_queue_empty(&port_mq->imq_messages));

	port_mq->imq_msgcount--;

	if (!imq_full(port_mq) && port_mq->imq_fullwaiters &&
		send_turnstile != TURNSTILE_NULL) {
		/*
		 * boost the priority of the awoken thread
		 * (WAITQ_PROMOTE_PRIORITY) to ensure it uses
		 * the message queue slot we've just reserved.
		 *
		 * NOTE: this will never prepost
		 *
		 * The wakeup happens on a turnstile waitq
		 * which will wakeup the highest priority waiter.
		 * A potential downside of this would be starving low
		 * priority senders if there is a constant churn of
		 * high priority threads trying to send to this port.
		 */
		if (waitq_wakeup64_one(&send_turnstile->ts_waitq,
					      IPC_MQUEUE_FULL,
					      THREAD_AWAKENED,
					      WAITQ_PROMOTE_PRIORITY) != KERN_SUCCESS) {
			port_mq->imq_fullwaiters = FALSE;
		} else {
			/* gave away our slot - add reference back */
			port_mq->imq_msgcount++;
		}
	}

	if (ipc_kmsg_queue_empty(&port_mq->imq_messages)) {
		/* no more msgs: invalidate the port's prepost object */
		waitq_clear_prepost_locked(&port_mq->imq_wait_queue);
	}
}