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
typedef  scalar_t__ thread_qos_t ;
struct uthread {struct kqrequest* uu_kqr_bound; } ;
struct kqworkq {int /*<<< orphan*/  kqwq_kqueue; } ;
struct kqrequest {scalar_t__ kqr_thread; int kqr_state; int /*<<< orphan*/  kqr_qos_index; int /*<<< orphan*/  kqr_suppressed; } ;
struct knote {int kn_status; } ;

/* Variables and functions */
 int KEVENT_FLAG_PARKING ; 
 int KN_STAYACTIVE ; 
 int KN_SUPPRESSED ; 
 int KQR_THREQUESTED ; 
 int KQR_WAKEUP ; 
 int KQWQAE_BEGIN_PROCESSING ; 
 int KQWQAE_UNBIND ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct knote* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ THREAD_QOS_UNSPECIFIED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ current_thread () ; 
 struct uthread* get_bsdthread_info (scalar_t__) ; 
 int /*<<< orphan*/  knote_unsuppress (struct knote*) ; 
 int /*<<< orphan*/  kq_req_lock (struct kqworkq*) ; 
 int /*<<< orphan*/  kq_req_unlock (struct kqworkq*) ; 
 int /*<<< orphan*/  kqlock_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kqueue_threadreq_initiate (int /*<<< orphan*/ *,struct kqrequest*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kqworkq_unbind_locked (struct kqworkq*,struct kqrequest*,scalar_t__) ; 
 int /*<<< orphan*/  thread_drop_ipc_override (scalar_t__) ; 

__attribute__((used)) static int
kqworkq_acknowledge_events(struct kqworkq *kqwq, struct kqrequest *kqr,
		int kevent_flags, int kqwqae_op)
{
	thread_qos_t old_override = THREAD_QOS_UNSPECIFIED;
	thread_t thread = kqr->kqr_thread;
	struct knote *kn;
	int rc = 0;
	bool seen_stayactive = false, unbind;

	kqlock_held(&kqwq->kqwq_kqueue);

	if (!TAILQ_EMPTY(&kqr->kqr_suppressed)) {
		/*
		 * Return suppressed knotes to their original state.
		 * For workq kqueues, suppressed ones that are still
		 * truly active (not just forced into the queue) will
		 * set flags we check below to see if anything got
		 * woken up.
		 */
		while ((kn = TAILQ_FIRST(&kqr->kqr_suppressed)) != NULL) {
			assert(kn->kn_status & KN_SUPPRESSED);
			knote_unsuppress(kn);
			if (kn->kn_status & KN_STAYACTIVE) {
				seen_stayactive = true;
			}
		}
	}

	kq_req_lock(kqwq);

#if DEBUG || DEVELOPMENT
	thread_t self = current_thread();
	struct uthread *ut = get_bsdthread_info(self);

	assert(kqr->kqr_state & KQR_THREQUESTED);
	assert(kqr->kqr_thread == self);
	assert(ut->uu_kqr_bound == kqr);
#endif // DEBUG || DEVELOPMENT

	if (kqwqae_op == KQWQAE_UNBIND) {
		unbind = true;
	} else if ((kevent_flags & KEVENT_FLAG_PARKING) == 0) {
		unbind = false;
	} else if (kqwqae_op == KQWQAE_BEGIN_PROCESSING && seen_stayactive) {
		/*
		 * When we unsuppress stayactive knotes, for the kind that are hooked
		 * through select, we need to process once before we can assert there's
		 * no event pending. Hence we can't unbind during BEGIN PROCESSING.
		 */
		unbind = false;
	} else {
		unbind = ((kqr->kqr_state & KQR_WAKEUP) == 0);
	}
	if (unbind) {
		old_override = kqworkq_unbind_locked(kqwq, kqr, thread);
		rc = -1;
		/*
		 * request a new thread if we didn't process the whole queue or real events
		 * have happened (not just putting stay-active events back).
		 */
		if (kqr->kqr_state & KQR_WAKEUP) {
			kqueue_threadreq_initiate(&kqwq->kqwq_kqueue, kqr,
					kqr->kqr_qos_index, 0);
		}
	}

	if (rc == 0) {
		/*
		 * Reset wakeup bit to notice events firing while we are processing,
		 * as we cannot rely on the bucket queue emptiness because of stay
		 * active knotes.
		 */
		kqr->kqr_state &= ~KQR_WAKEUP;
	}

	kq_req_unlock(kqwq);

	if (old_override) {
		thread_drop_ipc_override(thread);
	}

	return rc;
}