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
typedef  scalar_t__ thread_t ;
struct kqrequest {scalar_t__ kqr_thread; int /*<<< orphan*/  kqr_suppressed; } ;
struct kqueue {int kq_state; } ;
struct kqworkloop {struct kqrequest kqwl_request; struct kqueue kqwl_kqueue; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  scalar_t__ kq_index_t ;

/* Variables and functions */
 int KQWL_UTQ_PARKING ; 
 int KQ_PROCESSING ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ THREAD_QOS_UNSPECIFIED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  kq_req_lock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kq_req_unlock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kqlock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kqueue_release_last (int /*<<< orphan*/ ,struct kqworkloop*) ; 
 int /*<<< orphan*/  kqunlock (struct kqworkloop*) ; 
 scalar_t__ kqworkloop_acknowledge_events (struct kqworkloop*) ; 
 scalar_t__ kqworkloop_unbind_locked (struct kqworkloop*,scalar_t__) ; 
 int /*<<< orphan*/  kqworkloop_update_threads_qos (struct kqworkloop*,int,scalar_t__) ; 
 int /*<<< orphan*/  thread_drop_ipc_override (scalar_t__) ; 

__attribute__((used)) static void
kqworkloop_unbind(proc_t p, struct kqworkloop *kqwl)
{
	struct kqueue *kq = &kqwl->kqwl_kqueue;
	struct kqrequest *kqr = &kqwl->kqwl_request;
	thread_t thread = kqr->kqr_thread;
	int op = KQWL_UTQ_PARKING;
	kq_index_t ipc_override, qos_override = THREAD_QOS_UNSPECIFIED;

	assert(thread == current_thread());

	kqlock(kqwl);

	/*
	 * Forcing the KQ_PROCESSING flag allows for QoS updates because of
	 * unsuppressing knotes not to be applied until the eventual call to
	 * kqworkloop_update_threads_qos() below.
	 */
	assert((kq->kq_state & KQ_PROCESSING) == 0);
	if (!TAILQ_EMPTY(&kqr->kqr_suppressed)) {
		kq->kq_state |= KQ_PROCESSING;
		qos_override = kqworkloop_acknowledge_events(kqwl);
		kq->kq_state &= ~KQ_PROCESSING;
	}

	kq_req_lock(kqwl);

	ipc_override = kqworkloop_unbind_locked(kqwl, thread);
	kqworkloop_update_threads_qos(kqwl, op, qos_override);

	kq_req_unlock(kqwl);

	kqunlock(kqwl);

	/*
	 * Drop the override on the current thread last, after the call to
	 * kqworkloop_update_threads_qos above.
	 */
	if (ipc_override) {
		thread_drop_ipc_override(thread);
	}

	/* If last reference, dealloc the workloop kq */
	kqueue_release_last(p, kqwl);
}