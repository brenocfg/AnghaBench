#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tr_qos; } ;
struct kqrequest {int kqr_state; TYPE_1__ kqr_req; int /*<<< orphan*/  kqr_thread; } ;
struct kqworkloop {struct kqrequest kqwl_request; } ;
struct kqueue {int kq_state; } ;
struct knote {int kn_qos; } ;

/* Variables and functions */
 int KQR_THOVERCOMMIT ; 
 int KQR_THREQUESTED ; 
 int KQ_WORKLOOP ; 
 int _PTHREAD_PRIORITY_OVERCOMMIT_FLAG ; 
 struct kqueue* knote_get_kq (struct knote*) ; 
 int /*<<< orphan*/  kq_req_lock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kq_req_unlock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kqueue_threadreq_modify (struct kqueue*,struct kqrequest*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
knote_set_qos_overcommit(struct knote *kn)
{
	struct kqueue *kq = knote_get_kq(kn);

	/* turn overcommit on for the appropriate thread request? */
	if ((kn->kn_qos & _PTHREAD_PRIORITY_OVERCOMMIT_FLAG) &&
			(kq->kq_state & KQ_WORKLOOP)) {
		struct kqworkloop *kqwl = (struct kqworkloop *)kq;
		struct kqrequest *kqr = &kqwl->kqwl_request;

		/*
		 * This test is racy, but since we never remove this bit,
		 * it allows us to avoid taking a lock.
		 */
		if (kqr->kqr_state & KQR_THOVERCOMMIT) {
			return;
		}

		kq_req_lock(kqwl);
		kqr->kqr_state |= KQR_THOVERCOMMIT;
		if (!kqr->kqr_thread && (kqr->kqr_state & KQR_THREQUESTED)) {
			kqueue_threadreq_modify(kq, kqr, kqr->kqr_req.tr_qos);
		}
		kq_req_unlock(kqwl);
	}
}