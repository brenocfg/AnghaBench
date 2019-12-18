#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct proc {struct filedesc* p_fd; } ;
struct kqueue {struct proc* kq_p; int /*<<< orphan*/  kq_reqlock; int /*<<< orphan*/  kq_lock; int /*<<< orphan*/  kq_wqs; } ;
struct TYPE_4__ {int /*<<< orphan*/  kqr_suppressed; int /*<<< orphan*/  kqr_state; } ;
struct kqworkq {int kqwl_state; int kqwl_retains; int /*<<< orphan*/  kqf_suppressed; int /*<<< orphan*/  kqf_queue; struct kqueue kqf_kqueue; int /*<<< orphan*/  kqwl_statelock; TYPE_2__ kqwl_request; int /*<<< orphan*/ * kqwl_queue; struct kqueue kqwl_kqueue; TYPE_1__* kqwq_request; int /*<<< orphan*/ * kqwq_queue; int /*<<< orphan*/  kqwq_state; struct kqueue kqwq_kqueue; } ;
struct kqworkloop {int kqwl_state; int kqwl_retains; int /*<<< orphan*/  kqf_suppressed; int /*<<< orphan*/  kqf_queue; struct kqueue kqf_kqueue; int /*<<< orphan*/  kqwl_statelock; TYPE_2__ kqwl_request; int /*<<< orphan*/ * kqwl_queue; struct kqueue kqwl_kqueue; TYPE_1__* kqwq_request; int /*<<< orphan*/ * kqwq_queue; int /*<<< orphan*/  kqwq_state; struct kqueue kqwq_kqueue; } ;
struct kqfile {int kqwl_state; int kqwl_retains; int /*<<< orphan*/  kqf_suppressed; int /*<<< orphan*/  kqf_queue; struct kqueue kqf_kqueue; int /*<<< orphan*/  kqwl_statelock; TYPE_2__ kqwl_request; int /*<<< orphan*/ * kqwl_queue; struct kqueue kqwl_kqueue; TYPE_1__* kqwq_request; int /*<<< orphan*/ * kqwq_queue; int /*<<< orphan*/  kqwq_state; struct kqueue kqwq_kqueue; } ;
struct filedesc {scalar_t__ fd_knlistsize; } ;
struct TYPE_3__ {int kqr_qos_index; int /*<<< orphan*/  kqr_suppressed; int /*<<< orphan*/  kqr_state; } ;

/* Variables and functions */
 unsigned int KEVENT_FLAG_WORKLOOP ; 
 unsigned int KEVENT_FLAG_WORKQ ; 
 int /*<<< orphan*/  KQR_THOVERCOMMIT ; 
 int /*<<< orphan*/  KQR_WORKLOOP ; 
 int KQWL_NBUCKETS ; 
 int KQWQ_NBUCKETS ; 
 int KQWQ_QOS_MANAGER ; 
 int KQ_DYNAMIC ; 
 int KQ_WORKLOOP ; 
 int /*<<< orphan*/  KQ_WORKQ ; 
 int SYNC_POLICY_FIFO ; 
 int SYNC_POLICY_PREPOST ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct kqworkq*,int) ; 
 int /*<<< orphan*/  kq_lck_attr ; 
 int /*<<< orphan*/  kq_lck_grp ; 
 int /*<<< orphan*/  kqfile_zone ; 
 int /*<<< orphan*/  kqworkloop_zone ; 
 int /*<<< orphan*/  kqworkq_zone ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_spin_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdlock (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 
 int /*<<< orphan*/  waitq_set_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

struct kqueue *
kqueue_alloc(struct proc *p, unsigned int flags)
{
	struct filedesc *fdp = p->p_fd;
	struct kqueue *kq = NULL;
	int policy;
	void *hook = NULL;

	if (flags & KEVENT_FLAG_WORKQ) {
		struct kqworkq *kqwq;
		int i;

		kqwq = (struct kqworkq *)zalloc(kqworkq_zone);
		if (kqwq == NULL)
			return NULL;

		kq = &kqwq->kqwq_kqueue;
		bzero(kqwq, sizeof (struct kqworkq));

		kqwq->kqwq_state = KQ_WORKQ;

		for (i = 0; i < KQWQ_NBUCKETS; i++) {
			TAILQ_INIT(&kqwq->kqwq_queue[i]);
		}
		for (i = 0; i < KQWQ_NBUCKETS; i++) {
			if (i != KQWQ_QOS_MANAGER) {
				/*
				 * Because of how the bucketized system works, we mix overcommit
				 * sources with not overcommit: each time we move a knote from
				 * one bucket to the next due to overrides, we'd had to track
				 * overcommitness, and it's really not worth it in the workloop
				 * enabled world that track this faithfully.
				 *
				 * Incidentally, this behaves like the original manager-based
				 * kqwq where event delivery always happened (hence is
				 * "overcommit")
				 */
				kqwq->kqwq_request[i].kqr_state |= KQR_THOVERCOMMIT;
			}
			kqwq->kqwq_request[i].kqr_qos_index = i;
			TAILQ_INIT(&kqwq->kqwq_request[i].kqr_suppressed);
		}

		policy = SYNC_POLICY_FIFO;
		hook = (void *)kqwq;
	} else if (flags & KEVENT_FLAG_WORKLOOP) {
		struct kqworkloop *kqwl;
		int i;

		kqwl = (struct kqworkloop *)zalloc(kqworkloop_zone);
		if (kqwl == NULL)
			return NULL;

		bzero(kqwl, sizeof (struct kqworkloop));

		kqwl->kqwl_state = KQ_WORKLOOP | KQ_DYNAMIC;
		kqwl->kqwl_retains = 1; /* donate a retain to creator */
		kqwl->kqwl_request.kqr_state = KQR_WORKLOOP;

		kq = &kqwl->kqwl_kqueue;
		for (i = 0; i < KQWL_NBUCKETS; i++) {
			TAILQ_INIT(&kqwl->kqwl_queue[i]);
		}
		TAILQ_INIT(&kqwl->kqwl_request.kqr_suppressed);

		lck_mtx_init(&kqwl->kqwl_statelock, kq_lck_grp, kq_lck_attr);

		policy = SYNC_POLICY_FIFO;
		hook = (void *)kqwl;
	} else {
		struct kqfile *kqf;

		kqf = (struct kqfile *)zalloc(kqfile_zone);
		if (kqf == NULL)
			return NULL;

		kq = &kqf->kqf_kqueue;
		bzero(kqf, sizeof (struct kqfile));
		TAILQ_INIT(&kqf->kqf_queue);
		TAILQ_INIT(&kqf->kqf_suppressed);

		policy = SYNC_POLICY_FIFO | SYNC_POLICY_PREPOST;
	}

	waitq_set_init(&kq->kq_wqs, policy, NULL, hook);
	lck_spin_init(&kq->kq_lock, kq_lck_grp, kq_lck_attr);
	lck_spin_init(&kq->kq_reqlock, kq_lck_grp, kq_lck_attr);
	kq->kq_p = p;

	if (fdp->fd_knlistsize < 0) {
		proc_fdlock(p);
		if (fdp->fd_knlistsize < 0)
			fdp->fd_knlistsize = 0;	/* this process has had a kq */
		proc_fdunlock(p);
	}

	return (kq);
}