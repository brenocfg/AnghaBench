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
struct user_msghdr {int /*<<< orphan*/  msg_flags; scalar_t__ msg_controllen; scalar_t__ msg_control; scalar_t__ msg_iovlen; scalar_t__ msg_iov; int /*<<< orphan*/  msg_name; scalar_t__ msg_namelen; } ;
struct recvfrom_nocancel_args {int /*<<< orphan*/  fromlenaddr; int /*<<< orphan*/  s; int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; int /*<<< orphan*/  from; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DBG_FNC_RECVFROM ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int ENOMEM ; 
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_USERSPACE32 ; 
 int /*<<< orphan*/  UIO_USERSPACE64 ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fd ; 
 int recvit (struct proc*,int /*<<< orphan*/ ,struct user_msghdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uio_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_free (int /*<<< orphan*/ *) ; 

int
recvfrom_nocancel(struct proc *p, struct recvfrom_nocancel_args *uap,
    int32_t *retval)
{
	struct user_msghdr msg;
	int error;
	uio_t auio = NULL;

	KERNEL_DEBUG(DBG_FNC_RECVFROM | DBG_FUNC_START, 0, 0, 0, 0, 0);
	AUDIT_ARG(fd, uap->s);

	if (uap->fromlenaddr) {
		error = copyin(uap->fromlenaddr,
		    (caddr_t)&msg.msg_namelen, sizeof (msg.msg_namelen));
		if (error)
			return (error);
	} else {
		msg.msg_namelen = 0;
	}
	msg.msg_name = uap->from;
	auio = uio_create(1, 0,
	    (IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32),
	    UIO_READ);
	if (auio == NULL) {
		return (ENOMEM);
	}

	uio_addiov(auio, uap->buf, uap->len);
	/* no need to set up msg_iov.  recvit uses uio_t we send it */
	msg.msg_iov = 0;
	msg.msg_iovlen = 0;
	msg.msg_control = 0;
	msg.msg_controllen = 0;
	msg.msg_flags = uap->flags;
	error = recvit(p, uap->s, &msg, auio, uap->fromlenaddr, retval);
	if (auio != NULL) {
		uio_free(auio);
	}

	KERNEL_DEBUG(DBG_FNC_RECVFROM | DBG_FUNC_END, error, 0, 0, 0, 0);

	return (error);
}