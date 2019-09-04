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
struct user_msghdr {scalar_t__ msg_flags; scalar_t__ msg_control; scalar_t__ msg_iovlen; scalar_t__ msg_iov; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/  msg_name; } ;
struct socket {int dummy; } ;
struct sendto_nocancel_args {int /*<<< orphan*/  s; int /*<<< orphan*/  flags; int /*<<< orphan*/  tolen; int /*<<< orphan*/  to; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DBG_FNC_SENDTO ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int EBADF ; 
 int ENOMEM ; 
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_USERSPACE32 ; 
 int /*<<< orphan*/  UIO_USERSPACE64 ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  file_drop (int /*<<< orphan*/ ) ; 
 int file_socket (int /*<<< orphan*/ ,struct socket**) ; 
 int sendit (struct proc*,struct socket*,struct user_msghdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uio_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_free (int /*<<< orphan*/ *) ; 

int
sendto_nocancel(struct proc *p,
		struct sendto_nocancel_args *uap,
		int32_t *retval)
{
	struct user_msghdr msg;
	int error;
	uio_t auio = NULL;
	struct socket *so;

	KERNEL_DEBUG(DBG_FNC_SENDTO | DBG_FUNC_START, 0, 0, 0, 0, 0);
	AUDIT_ARG(fd, uap->s);

	auio = uio_create(1, 0,
	    (IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32),
	    UIO_WRITE);
	if (auio == NULL) {
		error = ENOMEM;
		goto done;
	}
	uio_addiov(auio, uap->buf, uap->len);

	msg.msg_name = uap->to;
	msg.msg_namelen = uap->tolen;
	/* no need to set up msg_iov.  sendit uses uio_t we send it */
	msg.msg_iov = 0;
	msg.msg_iovlen = 0;
	msg.msg_control = 0;
	msg.msg_flags = 0;

	error = file_socket(uap->s, &so);
	if (error)
		goto done;

	if (so == NULL) {
		error = EBADF;
	} else {
		error = sendit(p, so, &msg, auio, uap->flags, retval);
	}

	file_drop(uap->s);
done:
	if (auio != NULL)
		uio_free(auio);

	KERNEL_DEBUG(DBG_FNC_SENDTO | DBG_FUNC_END, error, *retval, 0, 0, 0);

	return (error);
}