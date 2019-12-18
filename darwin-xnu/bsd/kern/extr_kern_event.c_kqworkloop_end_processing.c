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
typedef  int /*<<< orphan*/  thread_t ;
typedef  size_t thread_qos_t ;
struct kqrequest {int kqr_state; int /*<<< orphan*/  kqr_wakeup_indexes; int /*<<< orphan*/  kqr_thread; } ;
struct kqueue {int kq_state; } ;
struct kqworkloop {int /*<<< orphan*/  kqwl_dynamicid; int /*<<< orphan*/  kqwl_owner; int /*<<< orphan*/ * kqwl_queue; struct kqrequest kqwl_request; struct kqueue kqwl_kqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSD_KEVENT_KQWL_PROCESS_END ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  KDBG_FILTERED (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int KEVENT_FLAG_PARKING ; 
 int KEV_EVTID (int /*<<< orphan*/ ) ; 
 int KQR_R2K_NOTIF_ARMED ; 
 int KQR_WAKEUP ; 
 int /*<<< orphan*/  KQUEUE_CANT_BE_LAST_REF ; 
 size_t KQWL_BUCKET_STAYACTIVE ; 
 int /*<<< orphan*/  KQWL_STAYACTIVE_FIRED_BIT ; 
 int /*<<< orphan*/  KQWL_UTQ_PARKING ; 
 int /*<<< orphan*/  KQWL_UTQ_RECOMPUTE_WAKEUP_QOS ; 
 int /*<<< orphan*/  KQWL_UTQ_UPDATE_WAKEUP_QOS ; 
 int KQ_PROCESSING ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 size_t THREAD_QOS_UNSPECIFIED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kq_req_lock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kq_req_unlock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kqlock_held (struct kqueue*) ; 
 int /*<<< orphan*/  kqueue_release (struct kqworkloop*,int /*<<< orphan*/ ) ; 
 size_t kqworkloop_acknowledge_events (struct kqworkloop*) ; 
 size_t kqworkloop_unbind_locked (struct kqworkloop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqworkloop_update_threads_qos (struct kqworkloop*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  thread_drop_ipc_override (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kqworkloop_end_processing(struct kqworkloop *kqwl, int flags, int kevent_flags)
{
	struct kqueue *kq = &kqwl->kqwl_kqueue;
	struct kqrequest *kqr = &kqwl->kqwl_request;
	thread_qos_t old_override = THREAD_QOS_UNSPECIFIED, qos_override;
	thread_t thread = kqr->kqr_thread;
	int rc = 0;

	kqlock_held(kq);

	KDBG_FILTERED(KEV_EVTID(BSD_KEVENT_KQWL_PROCESS_END) | DBG_FUNC_START,
			kqwl->kqwl_dynamicid, 0, 0);

	if (flags & KQ_PROCESSING) {
		assert(kq->kq_state & KQ_PROCESSING);

		/*
		 * If we still have queued stayactive knotes, remember we didn't finish
		 * processing all of them.  This should be extremely rare and would
		 * require to have a lot of them registered and fired.
		 */
		if (!TAILQ_EMPTY(&kqwl->kqwl_queue[KQWL_BUCKET_STAYACTIVE])) {
			kq_req_lock(kqwl);
			kqworkloop_update_threads_qos(kqwl, KQWL_UTQ_UPDATE_WAKEUP_QOS,
					KQWL_BUCKET_STAYACTIVE);
			kq_req_unlock(kqwl);
		}

		/*
		 * When KEVENT_FLAG_PARKING is set, we need to attempt an unbind while
		 * still under the lock.
		 *
		 * So we do everything kqworkloop_unbind() would do, but because we're
		 * inside kqueue_process(), if the workloop actually received events
		 * while our locks were dropped, we have the opportunity to fail the end
		 * processing and loop again.
		 *
		 * This avoids going through the process-wide workqueue lock hence
		 * scales better.
		 */
		if (kevent_flags & KEVENT_FLAG_PARKING) {
			qos_override = kqworkloop_acknowledge_events(kqwl);
		}
	}

	kq_req_lock(kqwl);

	if (kevent_flags & KEVENT_FLAG_PARKING) {
		kqworkloop_update_threads_qos(kqwl, KQWL_UTQ_PARKING, qos_override);
		if ((kqr->kqr_state & KQR_WAKEUP) && !kqwl->kqwl_owner) {
			/*
			 * Reset wakeup bit to notice stay active events firing while we are
			 * processing, as we cannot rely on the stayactive bucket emptiness.
			 */
			kqr->kqr_wakeup_indexes &= ~KQWL_STAYACTIVE_FIRED_BIT;
			rc = -1;
		} else {
			old_override = kqworkloop_unbind_locked(kqwl, thread);
			(void)kqueue_release(kqwl, KQUEUE_CANT_BE_LAST_REF);
			kq->kq_state &= ~flags;
		}
	} else {
		kq->kq_state &= ~flags;
		kqr->kqr_state |= KQR_R2K_NOTIF_ARMED;
		kqworkloop_update_threads_qos(kqwl, KQWL_UTQ_RECOMPUTE_WAKEUP_QOS, 0);
	}

	kq_req_unlock(kqwl);

	if (old_override) {
		thread_drop_ipc_override(thread);
	}

	KDBG_FILTERED(KEV_EVTID(BSD_KEVENT_KQWL_PROCESS_END) | DBG_FUNC_END,
			kqwl->kqwl_dynamicid, 0, 0);

	return rc;
}