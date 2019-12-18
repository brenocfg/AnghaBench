#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct fileproc {int dummy; } ;
struct filedesc {int fd_nfiles; int* fd_ofileflags; int /*<<< orphan*/ ** fd_ofiles; } ;
struct dup2_args {int from; int to; } ;
typedef  scalar_t__ rlim_t ;
typedef  TYPE_2__* proc_t ;
typedef  int int32_t ;
struct TYPE_18__ {TYPE_1__* p_rlimit; struct filedesc* p_fd; } ;
struct TYPE_17__ {scalar_t__ rlim_cur; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  FD_DUP2RESV ; 
 scalar_t__ FP_ISGUARDED (struct fileproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUARD_CLOSE ; 
 int /*<<< orphan*/  GUARD_DUP ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 size_t RLIMIT_NOFILE ; 
 int UF_RESERVED ; 
 int /*<<< orphan*/  close_internal_locked (TYPE_2__*,int,struct fileproc*,int /*<<< orphan*/ ) ; 
 int fdalloc (TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  fdrelse (TYPE_2__*,int) ; 
 int finishdup (TYPE_2__*,struct filedesc*,int,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  fp_drop (TYPE_2__*,int,struct fileproc*,int) ; 
 int fp_guard_exception (TYPE_2__*,int,struct fileproc*,int /*<<< orphan*/ ) ; 
 int fp_lookup (TYPE_2__*,int,struct fileproc**,int) ; 
 int /*<<< orphan*/  kGUARD_EXC_CLOSE ; 
 int /*<<< orphan*/  kGUARD_EXC_DUP ; 
 int maxfiles ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  proc_fdlock (TYPE_2__*) ; 
 int /*<<< orphan*/  proc_fdlock_assert (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (TYPE_2__*) ; 
 int /*<<< orphan*/  procfdtbl_clearfd (TYPE_2__*,int) ; 
 int /*<<< orphan*/  procfdtbl_reservefd (TYPE_2__*,int) ; 
 int /*<<< orphan*/  procfdtbl_waitfd (TYPE_2__*,int) ; 

int
dup2(proc_t p, struct dup2_args *uap, int32_t *retval)
{
	struct filedesc *fdp = p->p_fd;
	int old = uap->from, new = uap->to;
	int i, error;
	struct fileproc *fp, *nfp;

	proc_fdlock(p);

startover:
	if ( (error = fp_lookup(p, old, &fp, 1)) ) {
		proc_fdunlock(p);
		return(error);
	}
	if (FP_ISGUARDED(fp, GUARD_DUP)) {
		error = fp_guard_exception(p, old, fp, kGUARD_EXC_DUP);
		(void) fp_drop(p, old, fp, 1);
		proc_fdunlock(p);
		return (error);
	}
	if (new < 0 ||
		(rlim_t)new >= p->p_rlimit[RLIMIT_NOFILE].rlim_cur ||
	    new >= maxfiles) {
		fp_drop(p, old, fp, 1);
		proc_fdunlock(p);
		return (EBADF);
	}
	if (old == new) {
		fp_drop(p, old, fp, 1);
		*retval = new;
		proc_fdunlock(p);
		return (0);
	}
	if (new < 0 || new >= fdp->fd_nfiles) {
		if ( (error = fdalloc(p, new, &i)) ) {
			fp_drop(p, old, fp, 1);
			proc_fdunlock(p);
			return (error);
		}
		if (new != i) {
			fdrelse(p, i);
			goto closeit;
		}
	} else {
closeit:
		while ((fdp->fd_ofileflags[new] & UF_RESERVED) == UF_RESERVED)  {
				fp_drop(p, old, fp, 1);
				procfdtbl_waitfd(p, new);
#if DIAGNOSTIC
				proc_fdlock_assert(p, LCK_MTX_ASSERT_OWNED);
#endif
				goto startover;
		}

		if ((fdp->fd_ofiles[new] != NULL) &&
		    ((error = fp_lookup(p, new, &nfp, 1)) == 0)) {
			fp_drop(p, old, fp, 1);
			if (FP_ISGUARDED(nfp, GUARD_CLOSE)) {
				error = fp_guard_exception(p,
				    new, nfp, kGUARD_EXC_CLOSE);
				(void) fp_drop(p, new, nfp, 1);
				proc_fdunlock(p);
				return (error);
			}
			(void)close_internal_locked(p, new, nfp, FD_DUP2RESV);
#if DIAGNOSTIC
			proc_fdlock_assert(p, LCK_MTX_ASSERT_OWNED);
#endif
			procfdtbl_clearfd(p, new);
			goto startover;
		} else  {
#if DIAGNOSTIC
			if (fdp->fd_ofiles[new] != NULL)
				panic("dup2: no ref on fileproc %d", new);
#endif
			procfdtbl_reservefd(p, new);
		}

#if DIAGNOSTIC
		proc_fdlock_assert(p, LCK_MTX_ASSERT_OWNED);
#endif

	}
#if DIAGNOSTIC
	if (fdp->fd_ofiles[new] != 0)
		panic("dup2: overwriting fd_ofiles with new %d", new);
	if ((fdp->fd_ofileflags[new] & UF_RESERVED) == 0)
		panic("dup2: unreserved fileflags with new %d", new);
#endif
	error = finishdup(p, fdp, old, new, 0, retval);
	fp_drop(p, old, fp, 1);
	proc_fdunlock(p);

	return(error);
}