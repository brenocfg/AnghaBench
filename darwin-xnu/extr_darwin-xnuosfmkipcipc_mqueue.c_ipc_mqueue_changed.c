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
typedef  TYPE_1__* ipc_mqueue_t ;
struct TYPE_4__ {int /*<<< orphan*/  imq_wait_queue; int /*<<< orphan*/  imq_klist; } ;

/* Variables and functions */
 scalar_t__ IMQ_KLIST_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  IPC_MQUEUE_RECEIVE ; 
 int /*<<< orphan*/  THREAD_RESTART ; 
 int /*<<< orphan*/  WAITQ_ALL_PRIORITIES ; 
 int /*<<< orphan*/  WAITQ_KEEP_LOCKED ; 
 int /*<<< orphan*/  klist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knote_vanish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_wakeup64_all_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipc_mqueue_changed(
	ipc_mqueue_t		mqueue)
{
	if (IMQ_KLIST_VALID(mqueue)) {
		/*
		 * Indicate that this message queue is vanishing
		 *
		 * When this is called, the associated receive right may be in flight
		 * between two tasks: the one it used to live in, and the one that armed
		 * a port destroyed notification for it.
		 *
		 * The new process may want to register the port it gets back with an
		 * EVFILT_MACHPORT filter again, and may have pending sync IPC on this
		 * port pending already, in which case we want the imq_klist field to be
		 * reusable for nefarious purposes (see IMQ_SET_INHERITOR).
		 *
		 * Fortunately, we really don't need this linkage anymore after this
		 * point as EV_VANISHED / EV_EOF will be the last thing delivered ever.
		 */
		knote_vanish(&mqueue->imq_klist);
		klist_init(&mqueue->imq_klist);
	}

	waitq_wakeup64_all_locked(&mqueue->imq_wait_queue,
				  IPC_MQUEUE_RECEIVE,
				  THREAD_RESTART,
				  NULL,
				  WAITQ_ALL_PRIORITIES,
				  WAITQ_KEEP_LOCKED);
}