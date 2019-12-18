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
struct kqworkq {int /*<<< orphan*/  kqwq_kqueue; } ;
struct kqrequest {int kqr_state; } ;
typedef  int /*<<< orphan*/  kq_index_t ;

/* Variables and functions */
 int KQR_THREQUESTED ; 
 int KQR_WAKEUP ; 
 int /*<<< orphan*/  KQWQ_NBUCKETS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kq_req_lock (struct kqworkq*) ; 
 int /*<<< orphan*/  kq_req_unlock (struct kqworkq*) ; 
 int /*<<< orphan*/  kqueue_threadreq_initiate (int /*<<< orphan*/ *,struct kqrequest*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kqrequest* kqworkq_get_request (struct kqworkq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kqworkq_request_help(struct kqworkq *kqwq, kq_index_t qos_index)
{
	struct kqrequest *kqr;

	/* convert to thread qos value */
	assert(qos_index < KQWQ_NBUCKETS);

	kq_req_lock(kqwq);
	kqr = kqworkq_get_request(kqwq, qos_index);

	if ((kqr->kqr_state & KQR_WAKEUP) == 0) {
		kqr->kqr_state |= KQR_WAKEUP;
		if ((kqr->kqr_state & KQR_THREQUESTED) == 0) {
			kqueue_threadreq_initiate(&kqwq->kqwq_kqueue, kqr, qos_index, 0);
		}
	}
	kq_req_unlock(kqwq);
}