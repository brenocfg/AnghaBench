#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* uthread_t ;
typedef  void* user_size_t ;
typedef  int user_addr_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct user64_kevent {int dummy; } ;
struct user32_kevent {int dummy; } ;
struct timeval {int dummy; } ;
struct proc {int dummy; } ;
struct kqrequest {int /*<<< orphan*/  kqr_state; } ;
struct kqworkloop {scalar_t__ kqwl_dynamicid; struct kqrequest kqwl_request; } ;
struct kqueue {int kq_state; } ;
struct kevent_qos_s {int dummy; } ;
struct kevent_internal_s {int flags; int data; } ;
struct kevent64_s {int dummy; } ;
struct fileproc {int dummy; } ;
struct _kevent_register {int fd; int ueventlist; unsigned int flags; int* retval; int eventcount; int eventout; int /*<<< orphan*/  knote; struct fileproc* fp; struct kqueue* kq; struct kevent_internal_s kev; } ;
struct TYPE_14__ {int fp_fd; unsigned int fp_flags; int fp_data_out; void* fp_data_resid; void* fp_data_size; } ;
struct _kevent {int fd; int* retval; int eventlist; int eventcount; int eventout; TYPE_5__ process_data; scalar_t__ data_available; struct fileproc* fp; } ;
typedef  scalar_t__ kqueue_id_t ;
typedef  int /*<<< orphan*/  kqueue_continue_t ;
typedef  int int32_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* f_post_register_wait ) (TYPE_2__*,TYPE_4__*,struct _kevent_register*) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  knlc_knote; } ;
struct TYPE_11__ {struct _kevent uus_kevent; struct _kevent_register uus_kevent_register; } ;
struct TYPE_12__ {TYPE_1__ uu_save; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int ENOTSUP ; 
 int ERESTART ; 
 int EV_ERROR ; 
 int EV_RECEIPT ; 
 int EV_SYSFLAGS ; 
 int EWOULDBLOCK ; 
 int EXDEV ; 
 int FILTER_REGISTER_WAIT ; 
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 unsigned int KEVENT_FLAG_DYNAMIC_KQUEUE ; 
 unsigned int KEVENT_FLAG_DYNAMIC_KQ_MUST_EXIST ; 
 unsigned int KEVENT_FLAG_DYNAMIC_KQ_MUST_NOT_EXIST ; 
 unsigned int KEVENT_FLAG_ERROR_EVENTS ; 
 unsigned int KEVENT_FLAG_KERNEL ; 
 unsigned int KEVENT_FLAG_LEGACY32 ; 
 unsigned int KEVENT_FLAG_LEGACY64 ; 
 unsigned int KEVENT_FLAG_PARKING ; 
 unsigned int KEVENT_FLAG_STACK_EVENTS ; 
 unsigned int KEVENT_FLAG_WORKLOOP ; 
 unsigned int KEVENT_FLAG_WORKQ ; 
 int /*<<< orphan*/  KNOTE_KQ_UNLOCK ; 
 int /*<<< orphan*/  KNOTE_LOCK_CTX (TYPE_4__) ; 
 int /*<<< orphan*/  KQR_R2K_NOTIF_ARMED ; 
 int KQ_WORKLOOP ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ get_bsdthread_info (int /*<<< orphan*/ ) ; 
 scalar_t__ kevent_args_requesting_events (unsigned int,int) ; 
 int /*<<< orphan*/  kevent_callback ; 
 int kevent_copyin (int*,struct kevent_internal_s*,struct proc*,unsigned int) ; 
 int kevent_copyout (struct kevent_internal_s*,int*,struct proc*,unsigned int) ; 
 struct kqueue* kevent_get_bound_kqworkloop (int /*<<< orphan*/ ) ; 
 int kevent_get_data_size (struct proc*,scalar_t__,unsigned int,void**) ; 
 int kevent_get_kq (struct proc*,scalar_t__,int /*<<< orphan*/ *,unsigned int,struct fileproc**,int*,struct kqueue**) ; 
 int kevent_get_timeout (struct proc*,int,unsigned int,struct timeval*) ; 
 int /*<<< orphan*/  kevent_put_data_size (struct proc*,scalar_t__,unsigned int,void*) ; 
 int /*<<< orphan*/  kevent_put_kq (struct proc*,scalar_t__,struct fileproc*,struct kqueue*) ; 
 int kevent_register (struct kqueue*,struct kevent_internal_s*,TYPE_4__*) ; 
 TYPE_4__ knlc ; 
 TYPE_7__* knote_fops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knote_unlock (struct kqueue*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kq_req_lock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kq_req_unlock (struct kqueue*) ; 
 int /*<<< orphan*/  kqlock (struct kqueue*) ; 
 int /*<<< orphan*/  kqlock_held (struct kqueue*) ; 
 int kqueue_scan (struct kqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _kevent*,TYPE_5__*,struct timeval*,struct proc*) ; 
 int /*<<< orphan*/  kqunlock (struct kqueue*) ; 
 int /*<<< orphan*/  kqworkloop_end_processing (struct kqworkloop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct kevent_internal_s*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_4__*,struct _kevent_register*) ; 

__attribute__((used)) static int
kevent_internal(struct proc *p,
		kqueue_id_t id, kqueue_id_t *id_out,
		user_addr_t changelist, int nchanges,
		user_addr_t ueventlist, int nevents,
		user_addr_t data_out, uint64_t data_available,
		unsigned int flags,
		user_addr_t utimeout,
		kqueue_continue_t continuation,
		int32_t *retval)
{
	uthread_t ut;
	struct kqueue *kq;
	struct fileproc *fp = NULL;
	int fd = 0;
	struct kevent_internal_s kev;
	int error, noutputs, register_rc;
	bool needs_end_processing = false;
	struct timeval atv;
	user_size_t data_size;
	user_size_t data_resid;
	thread_t thread = current_thread();
	KNOTE_LOCK_CTX(knlc);

	/* Don't allow user-space threads to process output events from the workq kqs */
	if (((flags & (KEVENT_FLAG_WORKQ | KEVENT_FLAG_KERNEL)) == KEVENT_FLAG_WORKQ) &&
	    kevent_args_requesting_events(flags, nevents))
		return EINVAL;

	if (flags & KEVENT_FLAG_PARKING) {
		if (!kevent_args_requesting_events(flags, nevents) || id != (kqueue_id_t)-1)
			return EINVAL;
	}

	/* restrict dynamic kqueue allocation to workloops (for now) */
	if ((flags & (KEVENT_FLAG_DYNAMIC_KQUEUE | KEVENT_FLAG_WORKLOOP)) == KEVENT_FLAG_DYNAMIC_KQUEUE)
		return EINVAL;

	if ((flags & (KEVENT_FLAG_WORKLOOP)) && (flags & (KEVENT_FLAG_WORKQ)))
		return EINVAL;

	if (flags & (KEVENT_FLAG_DYNAMIC_KQ_MUST_EXIST | KEVENT_FLAG_DYNAMIC_KQ_MUST_NOT_EXIST)) {

		/* allowed only on workloops when calling kevent_id from user-space */
		if (!(flags & KEVENT_FLAG_WORKLOOP) || (flags & KEVENT_FLAG_KERNEL) || !(flags & KEVENT_FLAG_DYNAMIC_KQUEUE))
			return EINVAL;
	}

	/* prepare to deal with stack-wise allocation of out events */
	if (flags & KEVENT_FLAG_STACK_EVENTS) {
		int scale = ((flags & KEVENT_FLAG_LEGACY32) ?
			     (IS_64BIT_PROCESS(p) ? sizeof(struct user64_kevent) :
			                            sizeof(struct user32_kevent)) :
			     ((flags & KEVENT_FLAG_LEGACY64) ? sizeof(struct kevent64_s) :
			                                       sizeof(struct kevent_qos_s)));
		ueventlist += nevents * scale;
	}

	/* convert timeout to absolute - if we have one (and not immediate) */
	error = kevent_get_timeout(p, utimeout, flags, &atv);
	if (error)
		return error;

	/* copyin initial value of data residual from data_available */
	error = kevent_get_data_size(p, data_available, flags, &data_size);
	if (error)
		return error;

	/* get the kq we are going to be working on */
	error = kevent_get_kq(p, id, NULL, flags, &fp, &fd, &kq);
#if CONFIG_WORKLOOP_DEBUG
	ut = (uthread_t)get_bsdthread_info(thread);
	UU_KEVENT_HISTORY_WRITE_ENTRY(ut, {
		.uu_kqid = id,
		.uu_kq = error ? NULL : kq,
		.uu_error = error,
		.uu_nchanges = nchanges,
		.uu_nevents = nevents,
		.uu_flags = flags,
	});
#endif // CONFIG_WORKLOOP_DEBUG
	if (error)
		return error;

	/* only bound threads can receive events on workloops */
	if (flags & KEVENT_FLAG_WORKLOOP) {
		struct kqworkloop *kqwl = (struct kqworkloop *)kq;
		struct kqrequest *kqr = &kqwl->kqwl_request;

		assert(kq->kq_state & KQ_WORKLOOP);

		if (kevent_args_requesting_events(flags, nevents)) {
			if (kq != kevent_get_bound_kqworkloop(thread)) {
				error = EXDEV;
				goto out;
			}

			kq_req_lock(kqwl);
			/*
			 * Disable the R2K notification while doing a register, if the
			 * caller wants events too, we don't want the AST to be set if we
			 * will process these events soon.
			 */
			kqr->kqr_state &= ~KQR_R2K_NOTIF_ARMED;
			needs_end_processing = true;
			kq_req_unlock(kq);
		}

		if (id_out) {
			*id_out = kqwl->kqwl_dynamicid;
		}

	}

	/* register all the change requests the user provided... */
	noutputs = 0;
	while (nchanges > 0 && error == 0) {
		error = kevent_copyin(&changelist, &kev, p, flags);
		if (error)
			break;

		/* Make sure user doesn't pass in any system flags */
		kev.flags &= ~EV_SYSFLAGS;

		register_rc = kevent_register(kq, &kev, &knlc);
		if (register_rc & FILTER_REGISTER_WAIT) {
			kqlock_held(kq);

			// f_post_register_wait is meant to call a continuation and not to
			// return, which is why we don't support FILTER_REGISTER_WAIT if
			// KEVENT_FLAG_ERROR_EVENTS is not passed, or if the event that
			// waits isn't the last.
			//
			// It is implementable, but not used by any userspace code at the
			// moment, so for now return ENOTSUP if someone tries to do it.
			if (nchanges == 1 && nevents >= 1 && (flags & KEVENT_FLAG_ERROR_EVENTS)) {
				struct _kevent_register *cont_args;
				/* store the continuation/completion data in the uthread */
				ut = (uthread_t)get_bsdthread_info(thread);
				cont_args = &ut->uu_save.uus_kevent_register;
				cont_args->kev = kev;
				cont_args->kq = kq;
				cont_args->fp = fp;
				cont_args->fd = fd;
				cont_args->ueventlist = ueventlist;
				cont_args->flags = flags;
				cont_args->retval = retval;
				cont_args->eventcount = nevents;
				cont_args->eventout = noutputs;
				knote_fops(cont_args->knote)->f_post_register_wait(ut, &knlc, cont_args);
				panic("f_post_register_wait returned (kev: %p)", &kev);
			}

			kev.flags |= EV_ERROR;
			kev.data = ENOTSUP;
			knote_unlock(kq, knlc.knlc_knote, &knlc, KNOTE_KQ_UNLOCK);
		}

		// keep in sync with kevent_register_wait_return()
		if (nevents > 0 && (kev.flags & (EV_ERROR|EV_RECEIPT))) {
			if ((kev.flags & EV_ERROR) == 0) {
				kev.flags |= EV_ERROR;
				kev.data = 0;
			}
			error = kevent_copyout(&kev, &ueventlist, p, flags);
			if (error == 0) {
				nevents--;
				noutputs++;
			}
		} else if (kev.flags & EV_ERROR) {
			error = kev.data;
		}
		nchanges--;
	}

	/* short-circuit the scan if we only want error events */
	if (flags & KEVENT_FLAG_ERROR_EVENTS)
		nevents = 0;

	/* process pending events */
	if (nevents > 0 && noutputs == 0 && error == 0) {
		struct _kevent *cont_args;
		/* store the continuation/completion data in the uthread */
		ut = (uthread_t)get_bsdthread_info(thread);
		cont_args = &ut->uu_save.uus_kevent;
		cont_args->fp = fp;
		cont_args->fd = fd;
		cont_args->retval = retval;
		cont_args->eventlist = ueventlist;
		cont_args->eventcount = nevents;
		cont_args->eventout = noutputs;
		cont_args->data_available = data_available;
		cont_args->process_data.fp_fd = (int)id;
		cont_args->process_data.fp_flags = flags;
		cont_args->process_data.fp_data_out = data_out;
		cont_args->process_data.fp_data_size = data_size;
		cont_args->process_data.fp_data_resid = data_size;

		/*
		 * kqworkloop_end_processing() will happen at the end of kqueue_scan()
		 */
		needs_end_processing = false;

		error = kqueue_scan(kq, kevent_callback,
		                    continuation, cont_args,
		                    &cont_args->process_data,
		                    &atv, p);

		/* process remaining outputs */
		noutputs = cont_args->eventout;
		data_resid = cont_args->process_data.fp_data_resid;

		/* copyout residual data size value (if it needs to be copied out) */
		/* don't abandon other output just because of residual copyout failures */
		if (error == 0 && data_available && data_resid != data_size) {
			(void)kevent_put_data_size(p, data_available, flags, data_resid);
		}
	}

out:
	if (__improbable(needs_end_processing)) {
		/*
		 * If we didn't through kqworkloop_end_processing(),
		 * we need to do it here.
		 */
		kqlock(kq);
		kqworkloop_end_processing((struct kqworkloop *)kq, 0, 0);
		kqunlock(kq);
	}
	kevent_put_kq(p, id, fp, kq);

	/* don't restart after signals... */
	if (error == ERESTART)
		error = EINTR;
	else if (error == EWOULDBLOCK)
		error = 0;
	if (error == 0)
		*retval = noutputs;
	return (error);
}