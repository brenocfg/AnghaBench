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
typedef  int /*<<< orphan*/  user_ssize_t ;
typedef  int /*<<< orphan*/ * uio_t ;
struct user_iovec {int dummy; } ;
struct readv_nocancel_args {scalar_t__ iovcnt; int /*<<< orphan*/  fd; int /*<<< orphan*/  iovp; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 scalar_t__ UIO_MAXIOV ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_USERSPACE32 ; 
 int /*<<< orphan*/  UIO_USERSPACE64 ; 
 int copyin_user_iovec_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct user_iovec*) ; 
 int rd_uio (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uio_calculateresid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uio_create (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_free (int /*<<< orphan*/ *) ; 
 struct user_iovec* uio_iovsaddr (int /*<<< orphan*/ *) ; 

int
readv_nocancel(struct proc *p, struct readv_nocancel_args *uap, user_ssize_t *retval)
{
	uio_t auio = NULL;
	int error;
	struct user_iovec *iovp;

	/* Verify range bedfore calling uio_create() */
	if (uap->iovcnt <= 0 || uap->iovcnt > UIO_MAXIOV)
		return (EINVAL);

	/* allocate a uio large enough to hold the number of iovecs passed */
	auio = uio_create(uap->iovcnt, 0,
				  (IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32),
				  UIO_READ);
				  
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
	error = rd_uio(p, uap->fd, auio, retval);

ExitThisRoutine:
	if (auio != NULL) {
		uio_free(auio);
	}
	return (error);
}