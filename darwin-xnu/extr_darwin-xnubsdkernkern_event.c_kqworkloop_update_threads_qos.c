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
typedef  int /*<<< orphan*/ * thread_t ;
struct uthread {int uu_kqueue_override; } ;
struct kqueue {int dummy; } ;
struct kqrequest {int kqr_wakeup_indexes; int kqr_stayactive_qos; int kqr_state; int kqr_override_index; int kqr_qos_index; int /*<<< orphan*/ * kqr_thread; int /*<<< orphan*/  kqr_suppressed; } ;
struct kqworkloop {int /*<<< orphan*/  kqwl_dynamicid; int /*<<< orphan*/ * kqwl_owner; int /*<<< orphan*/ * kqwl_queue; struct kqueue kqwl_kqueue; struct kqrequest kqwl_request; } ;
typedef  int kq_index_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSD_KEVENT_KQWL_THADJUST ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KDBG_FILTERED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  KEV_EVTID (int /*<<< orphan*/ ) ; 
 int KQR_THREQUESTED ; 
 int KQR_WAKEUP ; 
 int KQWL_BUCKET_STAYACTIVE ; 
 int KQWL_STAYACTIVE_FIRED_BIT ; 
#define  KQWL_UTQ_PARKING 136 
#define  KQWL_UTQ_RECOMPUTE_WAKEUP_QOS 135 
#define  KQWL_UTQ_REDRIVE_EVENTS 134 
#define  KQWL_UTQ_RESET_WAKEUP_OVERRIDE 133 
#define  KQWL_UTQ_SET_QOS_INDEX 132 
#define  KQWL_UTQ_UNBINDING 131 
#define  KQWL_UTQ_UPDATE_STAYACTIVE_QOS 130 
#define  KQWL_UTQ_UPDATE_WAKEUP_OVERRIDE 129 
#define  KQWL_UTQ_UPDATE_WAKEUP_QOS 128 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int THREAD_QOS_UNSPECIFIED ; 
 scalar_t__ TRUE ; 
 int WORKQ_THREADREQ_ATTEMPT_REBIND ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fls (int) ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kq_req_held (struct kqworkloop*) ; 
 int /*<<< orphan*/  kqlock_held (struct kqworkloop*) ; 
 int /*<<< orphan*/  kqueue_threadreq_initiate (struct kqueue*,struct kqrequest*,int,int) ; 
 int /*<<< orphan*/  kqueue_threadreq_modify (struct kqueue*,struct kqrequest*,int) ; 
 int kqworkloop_owner_override (struct kqworkloop*) ; 
 int /*<<< orphan*/  kqworkloop_request_fire_r2k_notification (struct kqworkloop*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  thread_add_ipc_override (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  thread_drop_ipc_override (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_tid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_update_ipc_override (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
kqworkloop_update_threads_qos(struct kqworkloop *kqwl, int op, kq_index_t qos)
{
	struct kqrequest *kqr = &kqwl->kqwl_request;
	struct kqueue *kq = &kqwl->kqwl_kqueue;
	kq_index_t old_owner_override = kqworkloop_owner_override(kqwl);
	kq_index_t i;

	/* must hold the kqr lock */
	kq_req_held(kqwl);

	switch (op) {
	case KQWL_UTQ_UPDATE_WAKEUP_QOS:
		if (qos == KQWL_BUCKET_STAYACTIVE) {
			/*
			 * the KQWL_BUCKET_STAYACTIVE is not a QoS bucket, we only remember
			 * a high watermark (kqr_stayactive_qos) of any stay active knote
			 * that was ever registered with this workloop.
			 *
			 * When waitq_set__CALLING_PREPOST_HOOK__() wakes up any stay active
			 * knote, we use this high-watermark as a wakeup-index, and also set
			 * the magic KQWL_BUCKET_STAYACTIVE bit to make sure we remember
			 * there is at least one stay active knote fired until the next full
			 * processing of this bucket.
			 */
			kqr->kqr_wakeup_indexes |= KQWL_STAYACTIVE_FIRED_BIT;
			qos = kqr->kqr_stayactive_qos;
			assert(qos);
		}
		if (kqr->kqr_wakeup_indexes & (1 << qos)) {
			assert(kqr->kqr_state & KQR_WAKEUP);
			break;
		}

		kqr->kqr_wakeup_indexes |= (1 << qos);
		kqr->kqr_state |= KQR_WAKEUP;
		kqworkloop_request_fire_r2k_notification(kqwl);
		goto recompute;

	case KQWL_UTQ_UPDATE_STAYACTIVE_QOS:
		assert(qos);
		if (kqr->kqr_stayactive_qos < qos) {
			kqr->kqr_stayactive_qos = qos;
			if (kqr->kqr_wakeup_indexes & KQWL_STAYACTIVE_FIRED_BIT) {
				assert(kqr->kqr_state & KQR_WAKEUP);
				kqr->kqr_wakeup_indexes |= (1 << qos);
				goto recompute;
			}
		}
		break;

	case KQWL_UTQ_PARKING:
	case KQWL_UTQ_UNBINDING:
		kqr->kqr_override_index = qos;
		/* FALLTHROUGH */
	case KQWL_UTQ_RECOMPUTE_WAKEUP_QOS:
		if (op == KQWL_UTQ_RECOMPUTE_WAKEUP_QOS) {
			assert(qos == THREAD_QOS_UNSPECIFIED);
		}
		kqlock_held(kqwl); // to look at kq_queues
		i = KQWL_BUCKET_STAYACTIVE;
		if (TAILQ_EMPTY(&kqr->kqr_suppressed)) {
			kqr->kqr_override_index = THREAD_QOS_UNSPECIFIED;
		}
		if (!TAILQ_EMPTY(&kqwl->kqwl_queue[i]) &&
				(kqr->kqr_wakeup_indexes & KQWL_STAYACTIVE_FIRED_BIT)) {
			/*
			 * If the KQWL_STAYACTIVE_FIRED_BIT is set, it means a stay active
			 * knote may have fired, so we need to merge in kqr_stayactive_qos.
			 *
			 * Unlike other buckets, this one is never empty but could be idle.
			 */
			kqr->kqr_wakeup_indexes &= KQWL_STAYACTIVE_FIRED_BIT;
			kqr->kqr_wakeup_indexes |= (1 << kqr->kqr_stayactive_qos);
		} else {
			kqr->kqr_wakeup_indexes = 0;
		}
		for (i = THREAD_QOS_UNSPECIFIED + 1; i < KQWL_BUCKET_STAYACTIVE; i++) {
			if (!TAILQ_EMPTY(&kqwl->kqwl_queue[i])) {
				kqr->kqr_wakeup_indexes |= (1 << i);
			}
		}
		if (kqr->kqr_wakeup_indexes) {
			kqr->kqr_state |= KQR_WAKEUP;
			kqworkloop_request_fire_r2k_notification(kqwl);
		} else {
			kqr->kqr_state &= ~KQR_WAKEUP;
		}
		goto recompute;

	case KQWL_UTQ_RESET_WAKEUP_OVERRIDE:
		kqr->kqr_override_index = qos;
		goto recompute;

	case KQWL_UTQ_UPDATE_WAKEUP_OVERRIDE:
	recompute:
		/*
		 * When modifying the wakeup QoS or the override QoS, we always need to
		 * maintain our invariant that kqr_override_index is at least as large
		 * as the highest QoS for which an event is fired.
		 *
		 * However this override index can be larger when there is an overriden
		 * suppressed knote pushing on the kqueue.
		 */
		if (kqr->kqr_wakeup_indexes > (1 << qos)) {
			qos = fls(kqr->kqr_wakeup_indexes) - 1; /* fls is 1-based */
		}
		if (kqr->kqr_override_index < qos) {
			kqr->kqr_override_index = qos;
		}
		break;

	case KQWL_UTQ_REDRIVE_EVENTS:
		break;

	case KQWL_UTQ_SET_QOS_INDEX:
		kqr->kqr_qos_index = qos;
		break;

	default:
		panic("unknown kqwl thread qos update operation: %d", op);
	}

	thread_t kqwl_owner = kqwl->kqwl_owner;
	thread_t servicer = kqr->kqr_thread;
	boolean_t qos_changed = FALSE;
	kq_index_t new_owner_override = kqworkloop_owner_override(kqwl);

	/*
	 * Apply the diffs to the owner if applicable
	 */
	if (kqwl_owner) {
#if 0
		/* JMM - need new trace hooks for owner overrides */
		KDBG_FILTERED(KEV_EVTID(BSD_KEVENT_KQWL_THADJUST),
				kqwl->kqwl_dynamicid, thread_tid(kqwl_owner), kqr->kqr_qos_index,
				(kqr->kqr_override_index << 16) | kqr->kqr_state);
#endif
		if (new_owner_override == old_owner_override) {
			// nothing to do
		} else if (old_owner_override == THREAD_QOS_UNSPECIFIED) {
			thread_add_ipc_override(kqwl_owner, new_owner_override);
		} else if (new_owner_override == THREAD_QOS_UNSPECIFIED) {
			thread_drop_ipc_override(kqwl_owner);
		} else /*  old_owner_override != new_owner_override */ {
			thread_update_ipc_override(kqwl_owner, new_owner_override);
		}
	}

	/*
	 * apply the diffs to the servicer
	 */
	if ((kqr->kqr_state & KQR_THREQUESTED) == 0) {
		/*
		 * No servicer, nor thread-request
		 *
		 * Make a new thread request, unless there is an owner (or the workloop
		 * is suspended in userland) or if there is no asynchronous work in the
		 * first place.
		 */

		if (kqwl_owner == NULL && (kqr->kqr_state & KQR_WAKEUP)) {
			int initiate_flags = 0;
			if (op == KQWL_UTQ_UNBINDING) {
				initiate_flags = WORKQ_THREADREQ_ATTEMPT_REBIND;
			}
			kqueue_threadreq_initiate(kq, kqr, new_owner_override,
					initiate_flags);
		}
	} else if (servicer) {
		/*
		 * Servicer in flight
		 *
		 * Just apply the diff to the servicer
		 */
		struct uthread *ut = get_bsdthread_info(servicer);
		if (ut->uu_kqueue_override != kqr->kqr_override_index) {
			if (ut->uu_kqueue_override == THREAD_QOS_UNSPECIFIED) {
				thread_add_ipc_override(servicer, kqr->kqr_override_index);
			} else if (kqr->kqr_override_index == THREAD_QOS_UNSPECIFIED) {
				thread_drop_ipc_override(servicer);
			} else /* ut->uu_kqueue_override != kqr->kqr_override_index */ {
				thread_update_ipc_override(servicer, kqr->kqr_override_index);
			}
			ut->uu_kqueue_override = kqr->kqr_override_index;
			qos_changed = TRUE;
		}
	} else if (new_owner_override == THREAD_QOS_UNSPECIFIED) {
		/*
		 * No events to deliver anymore.
		 *
		 * However canceling with turnstiles is challenging, so the fact that
		 * the request isn't useful will be discovered by the servicer himself
		 * later on.
		 */
	} else if (old_owner_override != new_owner_override) {
		/*
		 * Request is in flight
		 *
		 * Apply the diff to the thread request
		 */
		kqueue_threadreq_modify(kq, kqr, new_owner_override);
		qos_changed = TRUE;
	}

	if (qos_changed) {
		KDBG_FILTERED(KEV_EVTID(BSD_KEVENT_KQWL_THADJUST), kqwl->kqwl_dynamicid,
				thread_tid(kqr->kqr_thread), kqr->kqr_qos_index,
				(kqr->kqr_override_index << 16) | kqr->kqr_state);
	}
}