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
struct kqueue {int kq_state; scalar_t__ kq_p; } ;
struct kqrequest {int kqr_state; scalar_t__ kqr_thread; } ;
typedef  int /*<<< orphan*/  kq_index_t ;

/* Variables and functions */
 int KQR_THREQUESTED ; 
 int KQ_WORKLOOP ; 
 scalar_t__ THREAD_NULL ; 
 int WORKQ_THREADREQ_SET_AST_ON_FAILURE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ current_proc () ; 
 int /*<<< orphan*/  kq_req_held (struct kqueue*) ; 
 int /*<<< orphan*/  workq_kern_threadreq_modify (scalar_t__,struct kqrequest*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
kqueue_threadreq_modify(struct kqueue *kq, struct kqrequest *kqr, kq_index_t qos)
{
	assert(kqr->kqr_state & KQR_THREQUESTED);
	assert(kqr->kqr_thread == THREAD_NULL);

	kq_req_held(kq);

	int flags = 0;
	if ((kq->kq_state & KQ_WORKLOOP) && kq->kq_p == current_proc()) {
		flags |= WORKQ_THREADREQ_SET_AST_ON_FAILURE;
	}
	workq_kern_threadreq_modify(kq->kq_p, kqr, qos, flags);
}