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
struct kqrequest {scalar_t__ kqr_qos_index; int /*<<< orphan*/  kqr_thread; scalar_t__ kqr_dsync_waiters; } ;
struct kqworkloop {int /*<<< orphan*/  kqwl_dynamicid; struct kqrequest kqwl_request; int /*<<< orphan*/  kqwl_owner; } ;
struct kqueue {int kq_state; } ;
struct TYPE_2__ {void** ext; } ;
struct knote {int kn_sfflags; int kn_flags; int /*<<< orphan*/  kn_id; int /*<<< orphan*/  kn_qos; TYPE_1__ kn_kevent; } ;
struct kevent_internal_s {scalar_t__ ident; scalar_t__ udata; int fflags; void** ext; } ;
typedef  int /*<<< orphan*/  kq_index_t ;

/* Variables and functions */
 int EALREADY ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOTSUP ; 
 int ERANGE ; 
 int ESTALE ; 
 int EV_CLEAR ; 
 int EV_DISABLE ; 
 int FILTER_ACTIVE ; 
 int /*<<< orphan*/  FILT_WLATTACH ; 
 int KQ_WORKLOOP ; 
 int NOTE_WL_COMMANDS_MASK ; 
 int NOTE_WL_END_OWNERSHIP ; 
 int NOTE_WL_IGNORE_ESTALE ; 
#define  NOTE_WL_SYNC_WAIT 130 
#define  NOTE_WL_SYNC_WAKE 129 
#define  NOTE_WL_THREAD_REQUEST 128 
 int /*<<< orphan*/  THREAD_QOS_UNSPECIFIED ; 
 int /*<<< orphan*/  _pthread_priority_thread_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 int filt_wlupdate (struct kqworkloop*,struct knote*,struct kevent_internal_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kevent_register_wait_prepare (struct knote*,struct kevent_internal_s*) ; 
 struct kqueue* knote_get_kq (struct knote*) ; 
 int /*<<< orphan*/  knote_set_error (struct knote*,int) ; 
 int /*<<< orphan*/  kq_req_lock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kq_req_unlock (struct kqworkloop*) ; 
 void* thread_owned_workloops_count (int /*<<< orphan*/ ) ; 
 void* thread_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_wlattach(struct knote *kn, struct kevent_internal_s *kev)
{
	struct kqueue *kq = knote_get_kq(kn);
	struct kqworkloop *kqwl = (struct kqworkloop *)kq;
	int error = 0;
	kq_index_t qos_index = 0;

	if ((kq->kq_state & KQ_WORKLOOP) == 0) {
		error = ENOTSUP;
		goto out;
	}

#if DEVELOPMENT || DEBUG
	if (kev->ident == 0 && kev->udata == 0 && kev->fflags == 0) {
		struct kqrequest *kqr = &kqwl->kqwl_request;

		kq_req_lock(kqwl);
		kev->fflags = 0;
		if (kqr->kqr_dsync_waiters) {
			kev->fflags |= NOTE_WL_SYNC_WAIT;
		}
		if (kqr->kqr_qos_index) {
			kev->fflags |= NOTE_WL_THREAD_REQUEST;
		}
		kev->ext[0] = thread_tid(kqwl->kqwl_owner);
		kev->ext[1] = thread_tid(kqwl->kqwl_request.kqr_thread);
		kev->ext[2] = thread_owned_workloops_count(current_thread());
		kev->ext[3] = kn->kn_kevent.ext[3];
		kq_req_unlock(kqwl);
		error = EBUSY;
		goto out;
	}
#endif

	int command = (kn->kn_sfflags & NOTE_WL_COMMANDS_MASK);
	switch (command) {
	case NOTE_WL_THREAD_REQUEST:
		if (kn->kn_id != kqwl->kqwl_dynamicid) {
			error = EINVAL;
			goto out;
		}
		qos_index = _pthread_priority_thread_qos(kn->kn_qos);
		if (qos_index == THREAD_QOS_UNSPECIFIED) {
			error = ERANGE;
			goto out;
		}
		if (kqwl->kqwl_request.kqr_qos_index) {
			/*
			 * There already is a thread request, and well, you're only allowed
			 * one per workloop, so fail the attach.
			 */
			error = EALREADY;
			goto out;
		}
		break;
	case NOTE_WL_SYNC_WAIT:
	case NOTE_WL_SYNC_WAKE:
		if (kn->kn_id == kqwl->kqwl_dynamicid) {
			error = EINVAL;
			goto out;
		}
		if ((kn->kn_flags & EV_DISABLE) == 0) {
			error = EINVAL;
			goto out;
		}
		if (kn->kn_sfflags & NOTE_WL_END_OWNERSHIP) {
			error = EINVAL;
			goto out;
		}
		break;
	default:
		error = EINVAL;
		goto out;
	}

	error = filt_wlupdate(kqwl, kn, kev, qos_index, FILT_WLATTACH);

out:
	if (error) {
		/* If userland wants ESTALE to be hidden, fail the attach anyway */
		if (error == ESTALE && (kn->kn_sfflags & NOTE_WL_IGNORE_ESTALE)) {
			error = 0;
		}
		knote_set_error(kn, error);
		return 0;
	}
	if (command == NOTE_WL_SYNC_WAIT) {
		return kevent_register_wait_prepare(kn, kev);
	}
	/* Just attaching the thread request successfully will fire it */
	if (command == NOTE_WL_THREAD_REQUEST) {
		/*
		 * Thread Request knotes need an explicit touch to be active again,
		 * so delivering an event needs to also consume it.
		 */
		kn->kn_flags |= EV_CLEAR;
		return FILTER_ACTIVE;
	}
	return 0;
}