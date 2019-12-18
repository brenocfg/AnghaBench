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
struct TYPE_2__ {int trp_flags; int /*<<< orphan*/  trp_cpupercent; int /*<<< orphan*/  trp_pol; int /*<<< orphan*/  trp_pri; int /*<<< orphan*/  trp_value; } ;
typedef  TYPE_1__ workq_threadreq_param_t ;
struct kqrequest {int /*<<< orphan*/  kqr_dsync_waiters; int /*<<< orphan*/  kqr_override_index; int /*<<< orphan*/  kqr_qos_index; int /*<<< orphan*/  kqr_state; int /*<<< orphan*/  kqr_thread; } ;
struct kqworkloop {int /*<<< orphan*/  kqwl_params; int /*<<< orphan*/  kqwl_owner; struct kqrequest kqwl_request; } ;
struct kqueue_dyninfo {int /*<<< orphan*/  kqdi_cpupercent; int /*<<< orphan*/  kqdi_pol; int /*<<< orphan*/  kqdi_pri; scalar_t__ kqdi_sync_waiter_qos; int /*<<< orphan*/  kqdi_sync_waiters; int /*<<< orphan*/  kqdi_events_qos; int /*<<< orphan*/  kqdi_async_qos; int /*<<< orphan*/  kqdi_request_state; void* kqdi_owner; void* kqdi_servicer; int /*<<< orphan*/  kqdi_info; } ;
struct kqueue {int kq_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int KQ_WORKLOOP ; 
 int TRP_CPUPERCENT ; 
 int TRP_POLICY ; 
 int TRP_PRIORITY ; 
 int fill_kqueueinfo (struct kqueue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kq_req_lock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kq_req_unlock (struct kqworkloop*) ; 
 void* thread_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fill_kqueue_dyninfo(struct kqueue *kq, struct kqueue_dyninfo *kqdi)
{
	struct kqworkloop *kqwl = (struct kqworkloop *)kq;
	struct kqrequest *kqr = &kqwl->kqwl_request;
	workq_threadreq_param_t trp = {};
	int err;

	if ((kq->kq_state & KQ_WORKLOOP) == 0) {
		return EINVAL;
	}

	if ((err = fill_kqueueinfo(kq, &kqdi->kqdi_info))) {
		return err;
	}

	kq_req_lock(kqwl);

	kqdi->kqdi_servicer = thread_tid(kqr->kqr_thread);
	kqdi->kqdi_owner = thread_tid(kqwl->kqwl_owner);
	kqdi->kqdi_request_state = kqr->kqr_state;
	kqdi->kqdi_async_qos = kqr->kqr_qos_index;
	kqdi->kqdi_events_qos = kqr->kqr_override_index;
	kqdi->kqdi_sync_waiters = kqr->kqr_dsync_waiters;
	kqdi->kqdi_sync_waiter_qos = 0;

	trp.trp_value = kqwl->kqwl_params;
	if (trp.trp_flags & TRP_PRIORITY)
		kqdi->kqdi_pri = trp.trp_pri;
	else
		kqdi->kqdi_pri = 0;

	if (trp.trp_flags & TRP_POLICY)
		kqdi->kqdi_pol = trp.trp_pol;
	else
		kqdi->kqdi_pol = 0;

	if (trp.trp_flags & TRP_CPUPERCENT)
		kqdi->kqdi_cpupercent = trp.trp_cpupercent;
	else
		kqdi->kqdi_cpupercent = 0;

	kq_req_unlock(kqwl);

	return 0;
}