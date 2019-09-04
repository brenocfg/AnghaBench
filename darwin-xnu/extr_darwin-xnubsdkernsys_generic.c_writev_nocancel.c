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
typedef  scalar_t__ user_ssize_t ;
typedef  int /*<<< orphan*/ * uio_t ;
struct writev_nocancel_args {scalar_t__ iovcnt; int /*<<< orphan*/  fd; int /*<<< orphan*/  iovp; } ;
struct user_iovec {int dummy; } ;
struct proc {int dummy; } ;
struct fileproc {int f_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EBADF ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ FP_ISGUARDED (struct fileproc*,int /*<<< orphan*/ ) ; 
 int FWRITE ; 
 int /*<<< orphan*/  GUARD_WRITE ; 
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 scalar_t__ UIO_MAXIOV ; 
 int /*<<< orphan*/  UIO_USERSPACE32 ; 
 int /*<<< orphan*/  UIO_USERSPACE64 ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int copyin_user_iovec_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct user_iovec*) ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  fp_drop (struct proc*,int /*<<< orphan*/ ,struct fileproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fp_drop_written (struct proc*,int /*<<< orphan*/ ,struct fileproc*) ; 
 int fp_guard_exception (struct proc*,int /*<<< orphan*/ ,struct fileproc*,int /*<<< orphan*/ ) ; 
 int fp_lookup (struct proc*,int /*<<< orphan*/ ,struct fileproc**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kGUARD_EXC_WRITE ; 
 int /*<<< orphan*/  proc_fdlock (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 
 int uio_calculateresid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uio_create (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_free (int /*<<< orphan*/ *) ; 
 struct user_iovec* uio_iovsaddr (int /*<<< orphan*/ *) ; 
 int wr_uio (struct proc*,struct fileproc*,int /*<<< orphan*/ *,scalar_t__*) ; 

int
writev_nocancel(struct proc *p, struct writev_nocancel_args *uap, user_ssize_t *retval)
{
	uio_t auio = NULL;
	int error;
	struct fileproc *fp;
	struct user_iovec *iovp;
	bool wrote_some = false;

	AUDIT_ARG(fd, uap->fd);

	/* Verify range bedfore calling uio_create() */
	if (uap->iovcnt <= 0 || uap->iovcnt > UIO_MAXIOV)
		return (EINVAL);

	/* allocate a uio large enough to hold the number of iovecs passed */
	auio = uio_create(uap->iovcnt, 0,
				  (IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32),
				  UIO_WRITE);
				  
	/* get location of iovecs within the uio.  then copyin the iovecs from
	 * user space.
	 */
	iovp = uio_iovsaddr(auio);
	if (iovp == NULL) {
		error = ENOMEM;
		goto ExitThisRoutine;
	}
	error = copyin_user_iovec_array(uap->iovp,
		IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32,
		uap->iovcnt, iovp);
	if (error) {
		goto ExitThisRoutine;
	}
	
	/* finalize uio_t for use and do the IO 
	 */
	error = uio_calculateresid(auio);
	if (error) {
		goto ExitThisRoutine;
	}

	error = fp_lookup(p, uap->fd, &fp, 0);
	if (error)
		goto ExitThisRoutine;
	
	if ((fp->f_flag & FWRITE) == 0) {
		error = EBADF;
	} else if (FP_ISGUARDED(fp, GUARD_WRITE)) {
		proc_fdlock(p);
		error = fp_guard_exception(p, uap->fd, fp, kGUARD_EXC_WRITE);
		proc_fdunlock(p);
	} else {
		error = wr_uio(p, fp, auio, retval);
		wrote_some = *retval > 0;
	}
	
	if (wrote_some)
	        fp_drop_written(p, uap->fd, fp);
	else
	        fp_drop(p, uap->fd, fp, 0);

ExitThisRoutine:
	if (auio != NULL) {
		uio_free(auio);
	}
	return (error);
}