#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct kqueue {int dummy; } ;
struct knote {int dummy; } ;
struct klist {int dummy; } ;
struct filedesc {int fd_knlistsize; scalar_t__ fd_knhashmask; struct klist* fd_knhash; struct klist* fd_knlist; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_7__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct klist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_KQUEUE ; 
 struct knote* SLIST_FIRST (struct klist*) ; 
 int /*<<< orphan*/  knhash_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  knhash_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  knote_drop (struct kqueue*,struct knote*,int /*<<< orphan*/ *) ; 
 struct kqueue* knote_get_kq (struct knote*) ; 
 int /*<<< orphan*/  kqlock (struct kqueue*) ; 
 int /*<<< orphan*/  proc_fdlock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_fdunlock (TYPE_1__*) ; 

void
knotes_dealloc(proc_t p)
{
	struct filedesc *fdp = p->p_fd;
	struct kqueue *kq;
	struct knote *kn;
	struct  klist *kn_hash = NULL;
	int i;

	/* Close all the fd-indexed knotes up front */
	if (fdp->fd_knlistsize > 0) {
		for (i = 0; i < fdp->fd_knlistsize; i++) {
			while ((kn = SLIST_FIRST(&fdp->fd_knlist[i])) != NULL) {
				kq = knote_get_kq(kn);
				kqlock(kq);
				proc_fdunlock(p);
				knote_drop(kq, kn, NULL);
				proc_fdlock(p);
			}
		}
		/* free the table */
		FREE(fdp->fd_knlist, M_KQUEUE);
		fdp->fd_knlist = NULL;
	}
	fdp->fd_knlistsize = -1;

	knhash_lock(p);
	proc_fdunlock(p);

	/* Clean out all the hashed knotes as well */
	if (fdp->fd_knhashmask != 0) {
		for (i = 0; i <= (int)fdp->fd_knhashmask; i++) {
			while ((kn = SLIST_FIRST(&fdp->fd_knhash[i])) != NULL) {
				kq = knote_get_kq(kn);
				kqlock(kq);
				knhash_unlock(p);
				knote_drop(kq, kn, NULL);
				knhash_lock(p);
			}
		}
		kn_hash = fdp->fd_knhash;
		fdp->fd_knhashmask = 0;
		fdp->fd_knhash = NULL;
	}

	knhash_unlock(p);

	/* free the kn_hash table */
	if (kn_hash)
		FREE(kn_hash, M_KQUEUE);

	proc_fdlock(p);
}