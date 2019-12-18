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
struct fileproc {int /*<<< orphan*/  f_fglob; } ;
struct filedesc {int* fd_ofileflags; scalar_t__* fd_ofiles; int fd_lastfile; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int int32_t ;

/* Variables and functions */
 int EBADF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int UF_RESERVED ; 
 int* fdflags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fdrelse (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fg_drop (struct fileproc*) ; 
 int /*<<< orphan*/  fg_ref (struct fileproc*) ; 
 struct fileproc* fileproc_alloc_init (int /*<<< orphan*/ *) ; 
 int mac_file_check_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  proc_fdlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdlock_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procfdtbl_releasefd (int /*<<< orphan*/ ,int,struct fileproc*) ; 

int
finishdup(proc_t p,
    struct filedesc *fdp, int old, int new, int fd_flags, int32_t *retval)
{
	struct fileproc *nfp;
	struct fileproc *ofp;
#if CONFIG_MACF
	int error;
#endif

#if DIAGNOSTIC
	proc_fdlock_assert(p, LCK_MTX_ASSERT_OWNED);
#endif
	if ((ofp = fdp->fd_ofiles[old]) == NULL ||
	    (fdp->fd_ofileflags[old] & UF_RESERVED)) {
		fdrelse(p, new);
		return (EBADF);
	}
	fg_ref(ofp);

#if CONFIG_MACF
	error = mac_file_check_dup(proc_ucred(p), ofp->f_fglob, new);
	if (error) {
		fg_drop(ofp);
		fdrelse(p, new);
		return (error);
	}
#endif

	proc_fdunlock(p);

	nfp = fileproc_alloc_init(NULL);

	proc_fdlock(p);

	if (nfp == NULL) {
		fg_drop(ofp);
		fdrelse(p, new);
		return (ENOMEM);
	}

	nfp->f_fglob = ofp->f_fglob;

#if DIAGNOSTIC
	if (fdp->fd_ofiles[new] != 0)
		panic("finishdup: overwriting fd_ofiles with new %d", new);
	if ((fdp->fd_ofileflags[new] & UF_RESERVED) == 0)
		panic("finishdup: unreserved fileflags with new %d", new);
#endif

	if (new > fdp->fd_lastfile)
		fdp->fd_lastfile = new;
	*fdflags(p, new) |= fd_flags;
	procfdtbl_releasefd(p, new, nfp);
	*retval = new;
	return (0);
}