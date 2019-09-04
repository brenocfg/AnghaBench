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
typedef  scalar_t__ thread_t ;
struct turnstile {int dummy; } ;
struct proc {struct filedesc* p_fd; } ;
struct TYPE_2__ {int kqr_state; } ;
struct kqworkq {scalar_t__ kqwl_retains; int /*<<< orphan*/  kqwl_statelock; int /*<<< orphan*/ * kqwl_turnstile; TYPE_1__ kqwl_request; } ;
struct kqworkloop {scalar_t__ kqwl_retains; int /*<<< orphan*/  kqwl_statelock; int /*<<< orphan*/ * kqwl_turnstile; TYPE_1__ kqwl_request; } ;
struct kqueue {int kq_state; int /*<<< orphan*/  kq_reqlock; int /*<<< orphan*/  kq_lock; int /*<<< orphan*/  kq_wqs; struct proc* kq_p; } ;
struct kqfile {scalar_t__ kqwl_retains; int /*<<< orphan*/  kqwl_statelock; int /*<<< orphan*/ * kqwl_turnstile; TYPE_1__ kqwl_request; } ;
struct knote {int dummy; } ;
struct filedesc {int fd_knlistsize; scalar_t__ fd_knhashmask; int /*<<< orphan*/ * fd_knhash; int /*<<< orphan*/ * fd_knlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_KQ_LOCK_ON_SUCCESS ; 
 int /*<<< orphan*/  KNOTE_LOCK_CTX (int /*<<< orphan*/ ) ; 
 int KQR_ALLOCATED_TURNSTILE ; 
 int KQ_WORKLOOP ; 
 int KQ_WORKQ ; 
 struct knote* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct knote* SLIST_NEXT (struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kn_link ; 
 int /*<<< orphan*/  knhash_lock (struct proc*) ; 
 int /*<<< orphan*/  knhash_unlock (struct proc*) ; 
 int /*<<< orphan*/  knlc ; 
 int /*<<< orphan*/  knote_drop (struct kqueue*,struct knote*,int /*<<< orphan*/ *) ; 
 struct kqueue* knote_get_kq (struct knote*) ; 
 scalar_t__ knote_lock (struct kqueue*,struct knote*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kq_lck_grp ; 
 int /*<<< orphan*/  kqfile_zone ; 
 int /*<<< orphan*/  kqlock (struct kqueue*) ; 
 scalar_t__ kqworkloop_invalidate (struct kqworkq*) ; 
 int /*<<< orphan*/  kqworkloop_zone ; 
 int /*<<< orphan*/  kqworkq_zone ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_spin_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdlock (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 
 int /*<<< orphan*/  thread_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  turnstile_cleanup () ; 
 int /*<<< orphan*/  turnstile_complete (uintptr_t,int /*<<< orphan*/ **,struct turnstile**) ; 
 int /*<<< orphan*/  turnstile_deallocate (struct turnstile*) ; 
 int /*<<< orphan*/  waitq_set_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct kqworkq*) ; 

void
kqueue_dealloc(struct kqueue *kq)
{
	struct proc *p;
	struct filedesc *fdp;
	struct knote *kn;
	int i;

	if (kq == NULL)
		return;

	p = kq->kq_p;
	fdp = p->p_fd;

	/*
	 * Workloops are refcounted by their knotes, so there's no point
	 * spending a lot of time under these locks just to deallocate one.
	 */
	if ((kq->kq_state & KQ_WORKLOOP) == 0) {
		KNOTE_LOCK_CTX(knlc);

		proc_fdlock(p);
		for (i = 0; i < fdp->fd_knlistsize; i++) {
			kn = SLIST_FIRST(&fdp->fd_knlist[i]);
			while (kn != NULL) {
				if (kq == knote_get_kq(kn)) {
					kqlock(kq);
					proc_fdunlock(p);
					if (knote_lock(kq, kn, &knlc, KNOTE_KQ_LOCK_ON_SUCCESS)) {
						knote_drop(kq, kn, &knlc);
					}
					proc_fdlock(p);
					/* start over at beginning of list */
					kn = SLIST_FIRST(&fdp->fd_knlist[i]);
					continue;
				}
				kn = SLIST_NEXT(kn, kn_link);
			}
		}

		knhash_lock(p);
		proc_fdunlock(p);

		if (fdp->fd_knhashmask != 0) {
			for (i = 0; i < (int)fdp->fd_knhashmask + 1; i++) {
				kn = SLIST_FIRST(&fdp->fd_knhash[i]);
				while (kn != NULL) {
					if (kq == knote_get_kq(kn)) {
						kqlock(kq);
						knhash_unlock(p);
						if (knote_lock(kq, kn, &knlc, KNOTE_KQ_LOCK_ON_SUCCESS)) {
							knote_drop(kq, kn, &knlc);
						}
						knhash_lock(p);
						/* start over at beginning of list */
						kn = SLIST_FIRST(&fdp->fd_knhash[i]);
						continue;
					}
					kn = SLIST_NEXT(kn, kn_link);
				}
			}
		}
		knhash_unlock(p);
	}

	if (kq->kq_state & KQ_WORKLOOP) {
		struct kqworkloop *kqwl = (struct kqworkloop *)kq;
		thread_t cur_owner = kqworkloop_invalidate(kqwl);

		if (cur_owner) thread_deallocate(cur_owner);

		if (kqwl->kqwl_request.kqr_state & KQR_ALLOCATED_TURNSTILE) {
			struct turnstile *ts;
			turnstile_complete((uintptr_t)kqwl, &kqwl->kqwl_turnstile, &ts);
			turnstile_cleanup();
			turnstile_deallocate(ts);
		} else {
			assert(kqwl->kqwl_turnstile == NULL);
		}
	}

	/*
	 * waitq_set_deinit() remove the KQ's waitq set from
	 * any select sets to which it may belong.
	 */
	waitq_set_deinit(&kq->kq_wqs);
	lck_spin_destroy(&kq->kq_lock, kq_lck_grp);
	lck_spin_destroy(&kq->kq_reqlock, kq_lck_grp);

	if (kq->kq_state & KQ_WORKQ) {
		zfree(kqworkq_zone, (struct kqworkq *)kq);
	} else if (kq->kq_state & KQ_WORKLOOP) {
		struct kqworkloop *kqwl = (struct kqworkloop *)kq;

		assert(kqwl->kqwl_retains == 0);
		lck_mtx_destroy(&kqwl->kqwl_statelock, kq_lck_grp);
		zfree(kqworkloop_zone, kqwl);
	} else {
		zfree(kqfile_zone, (struct kqfile *)kq);
	}
}