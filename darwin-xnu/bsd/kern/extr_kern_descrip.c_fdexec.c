#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
struct uthread {scalar_t__ uu_kqr_bound; } ;
struct kqueue {int dummy; } ;
struct fileproc {scalar_t__ f_iocount; int /*<<< orphan*/  f_fglob; } ;
struct filedesc {int fd_knlistsize; scalar_t__ fd_knhashmask; int fd_lastfile; char* fd_ofileflags; int fd_freefile; struct kqueue* fd_wqkqueue; struct fileproc** fd_ofiles; } ;
typedef  TYPE_1__* proc_t ;
typedef  int boolean_t ;
struct TYPE_10__ {int p_fpdrainwait; int /*<<< orphan*/  p_fdmlock; struct filedesc* p_fd; } ;

/* Variables and functions */
 short POSIX_SPAWN_CLOEXEC_DEFAULT ; 
 int /*<<< orphan*/  PRIBIO ; 
 char UF_EXCLOSE ; 
 char UF_INHERIT ; 
 char UF_RESERVED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  closef_locked (struct fileproc*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  fileproc_free (struct fileproc*) ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knotes_dealloc (TYPE_1__*) ; 
 int /*<<< orphan*/  kqueue_dealloc (struct kqueue*) ; 
 int /*<<< orphan*/  kqueue_threadreq_unbind (TYPE_1__*,scalar_t__) ; 
 scalar_t__ mac_file_check_inherit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_fdlock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_fdunlock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_ucred (TYPE_1__*) ; 
 int /*<<< orphan*/  procfdtbl_clearfd (TYPE_1__*,int) ; 

void
fdexec(proc_t p, short flags, int self_exec)
{
	struct filedesc *fdp = p->p_fd;
	int i;
	boolean_t cloexec_default = (flags & POSIX_SPAWN_CLOEXEC_DEFAULT) != 0;
	thread_t self = current_thread();
	struct uthread *ut = get_bsdthread_info(self);
	struct kqueue *dealloc_kq = NULL;

	/*
	 * If the current thread is bound as a workq/workloop
	 * servicing thread, we need to unbind it first.
	 */
	if (ut->uu_kqr_bound && self_exec) {
		kqueue_threadreq_unbind(p, ut->uu_kqr_bound);
	}

	proc_fdlock(p);

	/*
	 * Deallocate the knotes for this process
	 * and mark the tables non-existent so
	 * subsequent kqueue closes go faster.
	 */
	knotes_dealloc(p);
	assert(fdp->fd_knlistsize == -1);
	assert(fdp->fd_knhashmask == 0);

	for (i = fdp->fd_lastfile; i >= 0; i--) {

		struct fileproc *fp = fdp->fd_ofiles[i];
		char *flagp = &fdp->fd_ofileflags[i];

		if (fp && cloexec_default) {
			/*
			 * Reverse the usual semantics of file descriptor
			 * inheritance - all of them should be closed
			 * except files marked explicitly as "inherit" and
			 * not marked close-on-exec.
			 */
			if ((*flagp & (UF_EXCLOSE|UF_INHERIT)) != UF_INHERIT)
				*flagp |= UF_EXCLOSE;
			*flagp &= ~UF_INHERIT;
		}

		if (
		    ((*flagp & (UF_RESERVED|UF_EXCLOSE)) == UF_EXCLOSE)
#if CONFIG_MACF
		    || (fp && mac_file_check_inherit(proc_ucred(p), fp->f_fglob))
#endif
		) {
			procfdtbl_clearfd(p, i);
			if (i == fdp->fd_lastfile && i > 0)
				fdp->fd_lastfile--;
			if (i < fdp->fd_freefile)
				fdp->fd_freefile = i;

			/*
			 * Wait for any third party viewers (e.g., lsof)
			 * to release their references to this fileproc.
			 */
			while (fp->f_iocount > 0) {
				p->p_fpdrainwait = 1;
				msleep(&p->p_fpdrainwait, &p->p_fdmlock, PRIBIO,
				    "fpdrain", NULL);
			}

			closef_locked(fp, fp->f_fglob, p);

			fileproc_free(fp);
		}
	}

	/* release the per-process workq kq */
	if (fdp->fd_wqkqueue) {
		dealloc_kq = fdp->fd_wqkqueue;
		fdp->fd_wqkqueue = NULL;
	}
	   
	proc_fdunlock(p);

	/* Anything to free? */
	if (dealloc_kq)
		kqueue_dealloc(dealloc_kq);
}