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
typedef  int /*<<< orphan*/  uguard ;
struct user_iovec {int dummy; } ;
struct proc {int dummy; } ;
struct guarded_writev_np_args {scalar_t__ iovcnt; int /*<<< orphan*/  fd; int /*<<< orphan*/  guard; int /*<<< orphan*/  iovp; } ;
struct guarded_fileproc {int dummy; } ;
struct fileproc {int f_flag; } ;
typedef  int /*<<< orphan*/  guardid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EBADF ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FWRITE ; 
 struct fileproc* GFP_TO_FP (struct guarded_fileproc*) ; 
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 scalar_t__ UIO_MAXIOV ; 
 int /*<<< orphan*/  UIO_USERSPACE32 ; 
 int /*<<< orphan*/  UIO_USERSPACE64 ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int copyin_user_iovec_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct user_iovec*) ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  fp_drop (struct proc*,int /*<<< orphan*/ ,struct fileproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fp_drop_written (struct proc*,int /*<<< orphan*/ ,struct fileproc*) ; 
 int fp_lookup_guarded (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct guarded_fileproc**,int /*<<< orphan*/ ) ; 
 int uio_calculateresid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uio_create (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_free (int /*<<< orphan*/ *) ; 
 struct user_iovec* uio_iovsaddr (int /*<<< orphan*/ *) ; 
 int wr_uio (struct proc*,struct fileproc*,int /*<<< orphan*/ *,scalar_t__*) ; 

int
guarded_writev_np(struct proc *p, struct guarded_writev_np_args *uap, user_ssize_t *retval)
{
	uio_t auio = NULL;
	int error;
	struct fileproc *fp;
	struct user_iovec *iovp;
	guardid_t uguard;
	struct guarded_fileproc *gfp;
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

	if ((error = copyin(uap->guard, &uguard, sizeof (uguard))) != 0)
		goto ExitThisRoutine;

	error = fp_lookup_guarded(p, uap->fd, uguard, &gfp, 0);
	if (error)
		goto ExitThisRoutine;

	fp = GFP_TO_FP(gfp);
	if ((fp->f_flag & FWRITE) == 0) {
		error = EBADF;
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