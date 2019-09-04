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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/ * uio_t ;
struct user_msghdr {scalar_t__ msg_iovlen; int /*<<< orphan*/  msg_name; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_control; int /*<<< orphan*/  msg_controllen; int /*<<< orphan*/  msg_flags; } ;
struct user_iovec {int dummy; } ;
struct user64_msghdr {scalar_t__ msg_iovlen; int /*<<< orphan*/  msg_name; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_control; int /*<<< orphan*/  msg_controllen; int /*<<< orphan*/  msg_flags; } ;
struct user32_msghdr {scalar_t__ msg_iovlen; int /*<<< orphan*/  msg_name; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_control; int /*<<< orphan*/  msg_controllen; int /*<<< orphan*/  msg_flags; } ;
struct recvmsg_nocancel_args {int /*<<< orphan*/  msg; int /*<<< orphan*/  s; int /*<<< orphan*/  flags; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  msg64 ;
typedef  int /*<<< orphan*/  msg32 ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAST_USER_ADDR_T (struct user_iovec*) ; 
 int DBG_FNC_RECVMSG ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UIO_MAXIOV ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_USERSPACE32 ; 
 int /*<<< orphan*/  UIO_USERSPACE64 ; 
 int copyin (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int copyin_user_iovec_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct user_iovec*) ; 
 int copyout (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fd ; 
 int recvit (struct proc*,int /*<<< orphan*/ ,struct user_msghdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uio_calculateresid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uio_create (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_free (int /*<<< orphan*/ *) ; 
 struct user_iovec* uio_iovsaddr (int /*<<< orphan*/ *) ; 

int
recvmsg_nocancel(struct proc *p, struct recvmsg_nocancel_args *uap,
    int32_t *retval)
{
	struct user32_msghdr msg32;
	struct user64_msghdr msg64;
	struct user_msghdr user_msg;
	caddr_t msghdrp;
	int	size_of_msghdr;
	user_addr_t uiov;
	int error;
	uio_t auio = NULL;
	struct user_iovec *iovp;

	KERNEL_DEBUG(DBG_FNC_RECVMSG | DBG_FUNC_START, 0, 0, 0, 0, 0);
	AUDIT_ARG(fd, uap->s);
	if (IS_64BIT_PROCESS(p)) {
		msghdrp = (caddr_t)&msg64;
		size_of_msghdr = sizeof (msg64);
	} else {
		msghdrp = (caddr_t)&msg32;
		size_of_msghdr = sizeof (msg32);
	}
	error = copyin(uap->msg, msghdrp, size_of_msghdr);
	if (error) {
		KERNEL_DEBUG(DBG_FNC_RECVMSG | DBG_FUNC_END, error, 0, 0, 0, 0);
		return (error);
	}

	/* only need to copy if user process is not 64-bit */
	if (IS_64BIT_PROCESS(p)) {
		user_msg.msg_flags = msg64.msg_flags;
		user_msg.msg_controllen = msg64.msg_controllen;
		user_msg.msg_control = msg64.msg_control;
		user_msg.msg_iovlen = msg64.msg_iovlen;
		user_msg.msg_iov = msg64.msg_iov;
		user_msg.msg_namelen = msg64.msg_namelen;
		user_msg.msg_name = msg64.msg_name;
	} else {
		user_msg.msg_flags = msg32.msg_flags;
		user_msg.msg_controllen = msg32.msg_controllen;
		user_msg.msg_control = msg32.msg_control;
		user_msg.msg_iovlen = msg32.msg_iovlen;
		user_msg.msg_iov = msg32.msg_iov;
		user_msg.msg_namelen = msg32.msg_namelen;
		user_msg.msg_name = msg32.msg_name;
	}

	if (user_msg.msg_iovlen <= 0 || user_msg.msg_iovlen > UIO_MAXIOV) {
		KERNEL_DEBUG(DBG_FNC_RECVMSG | DBG_FUNC_END, EMSGSIZE,
		    0, 0, 0, 0);
		return (EMSGSIZE);
	}

	user_msg.msg_flags = uap->flags;

	/* allocate a uio large enough to hold the number of iovecs passed */
	auio = uio_create(user_msg.msg_iovlen, 0,
	    (IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32),
	    UIO_READ);
	if (auio == NULL) {
		error = ENOMEM;
		goto done;
	}

	/*
	 * get location of iovecs within the uio.  then copyin the iovecs from
	 * user space.
	 */
	iovp = uio_iovsaddr(auio);
	if (iovp == NULL) {
		error = ENOMEM;
		goto done;
	}
	uiov = user_msg.msg_iov;
	user_msg.msg_iov = CAST_USER_ADDR_T(iovp);
	error = copyin_user_iovec_array(uiov,
		IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32,
		user_msg.msg_iovlen, iovp);
	if (error)
		goto done;

	/* finish setup of uio_t */
	error = uio_calculateresid(auio);
	if (error) {
		goto done;
	}

	error = recvit(p, uap->s, &user_msg, auio, 0, retval);
	if (!error) {
		user_msg.msg_iov = uiov;
		if (IS_64BIT_PROCESS(p)) {
			msg64.msg_flags = user_msg.msg_flags;
			msg64.msg_controllen = user_msg.msg_controllen;
			msg64.msg_control = user_msg.msg_control;
			msg64.msg_iovlen = user_msg.msg_iovlen;
			msg64.msg_iov = user_msg.msg_iov;
			msg64.msg_namelen = user_msg.msg_namelen;
			msg64.msg_name = user_msg.msg_name;
		} else {
			msg32.msg_flags = user_msg.msg_flags;
			msg32.msg_controllen = user_msg.msg_controllen;
			msg32.msg_control = user_msg.msg_control;
			msg32.msg_iovlen = user_msg.msg_iovlen;
			msg32.msg_iov = user_msg.msg_iov;
			msg32.msg_namelen = user_msg.msg_namelen;
			msg32.msg_name = user_msg.msg_name;
		}
		error = copyout(msghdrp, uap->msg, size_of_msghdr);
	}
done:
	if (auio != NULL) {
		uio_free(auio);
	}
	KERNEL_DEBUG(DBG_FNC_RECVMSG | DBG_FUNC_END, error, 0, 0, 0, 0);
	return (error);
}