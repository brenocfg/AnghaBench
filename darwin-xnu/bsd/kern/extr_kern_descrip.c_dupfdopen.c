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
struct fileproc {int f_flag; int /*<<< orphan*/  f_fglob; } ;
struct filedesc {int fd_nfiles; int* fd_ofileflags; int fd_lastfile; struct fileproc** fd_ofiles; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int EACCES ; 
 int EBADF ; 
#define  ENODEV 128 
 int EPERM ; 
 int /*<<< orphan*/  FP_ISGUARDED (struct fileproc*,int /*<<< orphan*/ ) ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  GUARD_DUP ; 
 int O_CLOEXEC ; 
 int UF_EXCLOSE ; 
 int UF_RESERVED ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  fg_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fg_ref (struct fileproc*) ; 
 int mac_file_check_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_fdlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_ucred (int /*<<< orphan*/ ) ; 

int
dupfdopen(struct filedesc *fdp, int indx, int dfd, int flags, int error)
{
	struct fileproc *wfp;
	struct fileproc *fp;
#if CONFIG_MACF
	int myerror;
#endif
	proc_t p = current_proc();

	/*
	 * If the to-be-dup'd fd number is greater than the allowed number
	 * of file descriptors, or the fd to be dup'd has already been
	 * closed, reject.  Note, check for new == old is necessary as
	 * falloc could allocate an already closed to-be-dup'd descriptor
	 * as the new descriptor.
	 */
	proc_fdlock(p);

	fp = fdp->fd_ofiles[indx];
	if (dfd < 0 || dfd >= fdp->fd_nfiles ||
			(wfp = fdp->fd_ofiles[dfd]) == NULL || wfp == fp ||
	                (fdp->fd_ofileflags[dfd] & UF_RESERVED)) {

	        proc_fdunlock(p);
		return (EBADF);
	}
#if CONFIG_MACF
	myerror = mac_file_check_dup(proc_ucred(p), wfp->f_fglob, dfd);
	if (myerror) {
		proc_fdunlock(p);
		return (myerror);
	}
#endif
	/*
	 * There are two cases of interest here.
	 *
	 * For ENODEV simply dup (dfd) to file descriptor
	 * (indx) and return.
	 *
	 * For ENXIO steal away the file structure from (dfd) and
	 * store it in (indx).  (dfd) is effectively closed by
	 * this operation.
	 *
	 * Any other error code is just returned.
	 */
	switch (error) {
	case ENODEV:
		if (FP_ISGUARDED(wfp, GUARD_DUP)) {
			proc_fdunlock(p);
			return (EPERM);
		}

		/*
		 * Check that the mode the file is being opened for is a
		 * subset of the mode of the existing descriptor.
		 */
	        if (((flags & (FREAD|FWRITE)) | wfp->f_flag) != wfp->f_flag) {
		        proc_fdunlock(p);
			return (EACCES);
		}
		if (indx > fdp->fd_lastfile)
			fdp->fd_lastfile = indx;
		(void)fg_ref(wfp);

		if (fp->f_fglob)
		        fg_free(fp->f_fglob);
		fp->f_fglob = wfp->f_fglob;

		fdp->fd_ofileflags[indx] = fdp->fd_ofileflags[dfd] |
			(flags & O_CLOEXEC) ? UF_EXCLOSE : 0;

	        proc_fdunlock(p);
		return (0);

	default:
	        proc_fdunlock(p);
		return (error);
	}
	/* NOTREACHED */
}