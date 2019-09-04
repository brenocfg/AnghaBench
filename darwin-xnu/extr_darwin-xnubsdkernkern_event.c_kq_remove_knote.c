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
typedef  int uint16_t ;
typedef  size_t u_int ;
struct proc {struct filedesc* p_fd; } ;
struct kqueue {int kq_state; } ;
struct knote_lock_ctx {int dummy; } ;
struct knote {size_t kn_id; } ;
struct klist {int dummy; } ;
struct filedesc {int /*<<< orphan*/  fd_knhashmask; struct klist* fd_knhash; struct klist* fd_knlist; scalar_t__ fd_knlistsize; } ;
struct TYPE_2__ {int f_isfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_KQ_UNLOCK ; 
 size_t KN_HASH (size_t,int /*<<< orphan*/ ) ; 
 int KQ_DYNAMIC ; 
 int /*<<< orphan*/  SLIST_REMOVE (struct klist*,struct knote*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kn_link ; 
 int /*<<< orphan*/  knhash_lock (struct proc*) ; 
 int /*<<< orphan*/  knhash_unlock (struct proc*) ; 
 int /*<<< orphan*/  knote ; 
 TYPE_1__* knote_fops (struct knote*) ; 
 int /*<<< orphan*/  knote_unlock_cancel (struct kqueue*,struct knote*,struct knote_lock_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqlock (struct kqueue*) ; 
 int /*<<< orphan*/  kqueue_release_last (struct proc*,struct kqueue*) ; 
 int /*<<< orphan*/  kqunlock (struct kqueue*) ; 
 int /*<<< orphan*/  proc_fdlock (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 

__attribute__((used)) static void
kq_remove_knote(struct kqueue *kq, struct knote *kn, struct proc *p,
		struct knote_lock_ctx *knlc)
{
	struct filedesc *fdp = p->p_fd;
	struct klist *list = NULL;
	uint16_t kq_state;
	bool is_fd;

	is_fd = knote_fops(kn)->f_isfd;

	if (is_fd)
		proc_fdlock(p);
	else
		knhash_lock(p);

	if (is_fd) {
		assert ((u_int)fdp->fd_knlistsize > kn->kn_id);
		list = &fdp->fd_knlist[kn->kn_id];
	} else {
		list = &fdp->fd_knhash[KN_HASH(kn->kn_id, fdp->fd_knhashmask)];
	}
	SLIST_REMOVE(list, kn, knote, kn_link);

	kqlock(kq);
	kq_state = kq->kq_state;
	if (knlc) {
		knote_unlock_cancel(kq, kn, knlc, KNOTE_KQ_UNLOCK);
	} else {
		kqunlock(kq);
	}
	if (is_fd)
		proc_fdunlock(p);
	else
		knhash_unlock(p);

	if (kq_state & KQ_DYNAMIC)
		kqueue_release_last(p, kq);
}