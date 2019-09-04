#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct turnstile {int /*<<< orphan*/  ts_waitq; } ;
typedef  scalar_t__ mach_port_msgcount_t ;
typedef  TYPE_1__* ipc_mqueue_t ;
struct TYPE_6__ {scalar_t__ imq_qlimit; int /*<<< orphan*/  imq_msgcount; int /*<<< orphan*/  imq_fullwaiters; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IPC_MQUEUE_FULL ; 
 scalar_t__ KERN_NOT_WAITING ; 
 scalar_t__ MACH_PORT_QLIMIT_MAX ; 
 int /*<<< orphan*/  THREAD_AWAKENED ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  WAITQ_PROMOTE_PRIORITY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  imq_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  imq_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_from_mq (TYPE_1__*) ; 
 struct turnstile* port_send_turnstile (int /*<<< orphan*/ ) ; 
 scalar_t__ waitq_wakeup64_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipc_mqueue_set_qlimit(
	 ipc_mqueue_t			mqueue,
	 mach_port_msgcount_t	qlimit)
{

	 assert(qlimit <= MACH_PORT_QLIMIT_MAX);

	 /* wake up senders allowed by the new qlimit */
	 imq_lock(mqueue);
	 if (qlimit > mqueue->imq_qlimit) {
		 mach_port_msgcount_t i, wakeup;
		 struct turnstile *send_turnstile = port_send_turnstile(ip_from_mq(mqueue));

		 /* caution: wakeup, qlimit are unsigned */
		 wakeup = qlimit - mqueue->imq_qlimit;

		 for (i = 0; i < wakeup; i++) {
			/*
			 * boost the priority of the awoken thread
			 * (WAITQ_PROMOTE_PRIORITY) to ensure it uses
			 * the message queue slot we've just reserved.
			 *
			 * NOTE: this will never prepost
			 */
			if (send_turnstile == TURNSTILE_NULL ||
			    waitq_wakeup64_one(&send_turnstile->ts_waitq,
					       IPC_MQUEUE_FULL,
					       THREAD_AWAKENED,
					       WAITQ_PROMOTE_PRIORITY) == KERN_NOT_WAITING) {
				mqueue->imq_fullwaiters = FALSE;
				break;
			}
			mqueue->imq_msgcount++;  /* give it to the awakened thread */
		 }
	}
	mqueue->imq_qlimit = qlimit;
	imq_unlock(mqueue);
}