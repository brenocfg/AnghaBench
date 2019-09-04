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
struct kqworkloop {int dummy; } ;
struct kqueue {int kq_state; } ;
struct kqtailq {int dummy; } ;
struct knote {int kn_status; int /*<<< orphan*/  kn_qos_override; int /*<<< orphan*/  kn_qos_index; int /*<<< orphan*/  kn_req_index; } ;

/* Variables and functions */
 int KN_ACTIVE ; 
 int KN_SUPPRESSED ; 
 int /*<<< orphan*/  KQWL_UTQ_RESET_WAKEUP_OVERRIDE ; 
 int KQ_WORKLOOP ; 
 scalar_t__ TAILQ_EMPTY (struct kqtailq*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct kqtailq*,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kn_tqe ; 
 scalar_t__ knote_enqueue (struct knote*) ; 
 struct kqueue* knote_get_kq (struct knote*) ; 
 int /*<<< orphan*/  knote_wakeup (struct knote*) ; 
 int /*<<< orphan*/  kq_req_lock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kq_req_unlock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kqlock_held (struct kqueue*) ; 
 struct kqtailq* kqueue_get_suppressed_queue (struct kqueue*,struct knote*) ; 
 scalar_t__ kqworkloop_is_processing_on_current_thread (struct kqworkloop*) ; 
 int /*<<< orphan*/  kqworkloop_update_threads_qos (struct kqworkloop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
knote_unsuppress(struct knote *kn)
{
	struct kqtailq *suppressq;
	struct kqueue *kq = knote_get_kq(kn);

	kqlock_held(kq);

	if ((kn->kn_status & KN_SUPPRESSED) == 0)
		return;

	kn->kn_status &= ~KN_SUPPRESSED;
	suppressq = kqueue_get_suppressed_queue(kq, kn);
	TAILQ_REMOVE(suppressq, kn, kn_tqe);

	/*
	 * If the knote is no longer active, reset its push,
	 * and resynchronize kn_qos_index with kn_qos_override
	 */
	if ((kn->kn_status & KN_ACTIVE) == 0) {
		kn->kn_qos_override = kn->kn_req_index;
	}
	kn->kn_qos_index = kn->kn_qos_override;

	/* don't wakeup if unsuppressing just a stay-active knote */
	if (knote_enqueue(kn) && (kn->kn_status & KN_ACTIVE)) {
		knote_wakeup(kn);
	}

	if ((kq->kq_state & KQ_WORKLOOP) && TAILQ_EMPTY(suppressq)) {
		struct kqworkloop *kqwl = (struct kqworkloop *)kq;

		if (kqworkloop_is_processing_on_current_thread(kqwl)) {
			/*
			 * kqworkloop_end_processing() or kqworkloop_begin_processing()
			 * will perform the required QoS computations when it unsets the
			 * processing mode.
			 */
		} else {
			kq_req_lock(kqwl);
			kqworkloop_update_threads_qos(kqwl, KQWL_UTQ_RESET_WAKEUP_OVERRIDE, 0);
			kq_req_unlock(kqwl);
		}
	}
}