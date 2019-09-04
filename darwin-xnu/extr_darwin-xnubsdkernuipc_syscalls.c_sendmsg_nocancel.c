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
typedef  int /*<<< orphan*/ * uio_t ;
struct user_msghdr {scalar_t__ msg_iovlen; scalar_t__ msg_flags; scalar_t__ msg_iov; int /*<<< orphan*/  msg_name; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/  msg_control; int /*<<< orphan*/  msg_controllen; } ;
struct user_iovec {int dummy; } ;
struct user64_msghdr {scalar_t__ msg_iovlen; int /*<<< orphan*/  msg_name; int /*<<< orphan*/  msg_namelen; scalar_t__ msg_iov; int /*<<< orphan*/  msg_control; int /*<<< orphan*/  msg_controllen; scalar_t__ msg_flags; } ;
struct user32_msghdr {scalar_t__ msg_iovlen; int /*<<< orphan*/  msg_name; int /*<<< orphan*/  msg_namelen; scalar_t__ msg_iov; int /*<<< orphan*/  msg_control; int /*<<< orphan*/  msg_controllen; scalar_t__ msg_flags; } ;
struct socket {int dummy; } ;
struct sendmsg_nocancel_args {int /*<<< orphan*/  s; int /*<<< orphan*/  flags; int /*<<< orphan*/  msg; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  msg64 ;
typedef  int /*<<< orphan*/  msg32 ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CAST_USER_ADDR_T (struct user_iovec*) ; 
 int DBG_FNC_SENDMSG ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int EBADF ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UIO_MAXIOV ; 
 int /*<<< orphan*/  UIO_USERSPACE32 ; 
 int /*<<< orphan*/  UIO_USERSPACE64 ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int copyin (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int copyin_user_iovec_array (scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct user_iovec*) ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  file_drop (int /*<<< orphan*/ ) ; 
 int file_socket (int /*<<< orphan*/ ,struct socket**) ; 
 int sendit (struct proc*,struct socket*,struct user_msghdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uio_calculateresid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uio_create (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_free (int /*<<< orphan*/ *) ; 
 struct user_iovec* uio_iovsaddr (int /*<<< orphan*/ *) ; 

int
sendmsg_nocancel(struct proc *p, struct sendmsg_nocancel_args *uap,
    int32_t *retval)
{
	struct user32_msghdr msg32;
	struct user64_msghdr msg64;
	struct user_msghdr user_msg;
	caddr_t msghdrp;
	int	size_of_msghdr;
	int error;
	uio_t auio = NULL;
	struct user_iovec *iovp;
	struct socket *so;

	KERNEL_DEBUG(DBG_FNC_SENDMSG | DBG_FUNC_START, 0, 0, 0, 0, 0);
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
		KERNEL_DEBUG(DBG_FNC_SENDMSG | DBG_FUNC_END, error, 0, 0, 0, 0);
		return (error);
	}

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
		KERNEL_DEBUG(DBG_FNC_SENDMSG | DBG_FUNC_END, EMSGSIZE,
		    0, 0, 0, 0);
		return (EMSGSIZE);
	}

	/* allocate a uio large enough to hold the number of iovecs passed */
	auio = uio_create(user_msg.msg_iovlen, 0,
	    (IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32),
	    UIO_WRITE);
	if (auio == NULL) {
		error = ENOBUFS;
		goto done;
	}

	if (user_msg.msg_iovlen) {
		/*
		 * get location of iovecs within the uio.
		 * then copyin the iovecs from user space.
		 */
		iovp = uio_iovsaddr(auio);
		if (iovp == NULL) {
			error = ENOBUFS;
			goto done;
		}
		error = copyin_user_iovec_array(user_msg.msg_iov,
			IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32,
			user_msg.msg_iovlen, iovp);
		if (error)
			goto done;
		user_msg.msg_iov = CAST_USER_ADDR_T(iovp);

		/* finish setup of uio_t */
		error = uio_calculateresid(auio);
		if (error) {
			goto done;
		}
	} else {
		user_msg.msg_iov = 0;
	}

	/* msg_flags is ignored for send */
	user_msg.msg_flags = 0;

	error = file_socket(uap->s, &so);
	if (error) {
		goto done;
	}
	if (so == NULL) {
		error = EBADF;
	} else {
		error = sendit(p, so, &user_msg, auio, uap->flags, retval);
	}
	file_drop(uap->s);
done:
	if (auio != NULL) {
		uio_free(auio);
	}
	KERNEL_DEBUG(DBG_FNC_SENDMSG | DBG_FUNC_END, error, 0, 0, 0, 0);

	return (error);
}