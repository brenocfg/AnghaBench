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
struct user_sa_endpoints {scalar_t__ sae_srcaddr; int sae_srcaddrlen; scalar_t__ sae_dstaddr; int sae_dstaddrlen; int /*<<< orphan*/  sae_srcif; } ;
struct user_iovec {int dummy; } ;
struct user64_sa_endpoints {scalar_t__ sae_srcaddr; int sae_srcaddrlen; scalar_t__ sae_dstaddr; int sae_dstaddrlen; int /*<<< orphan*/  sae_srcif; } ;
struct user32_sa_endpoints {scalar_t__ sae_srcaddr; int sae_srcaddrlen; scalar_t__ sae_dstaddr; int sae_dstaddrlen; int /*<<< orphan*/  sae_srcif; } ;
struct socket {scalar_t__ so_type; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct proc {int dummy; } ;
struct connectx_args {int socket; scalar_t__ endpoints; scalar_t__ iov; scalar_t__ iovcnt; scalar_t__ len; scalar_t__ connid; int /*<<< orphan*/  flags; int /*<<< orphan*/  associd; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  sd ;
typedef  int /*<<< orphan*/  sae_connid_t ;
typedef  int /*<<< orphan*/  ep64 ;
typedef  int /*<<< orphan*/  ep32 ;
typedef  int /*<<< orphan*/  cid ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int,int) ; 
 int EBADF ; 
 int EINTR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ERESTART ; 
 int /*<<< orphan*/  FREE (struct sockaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 int /*<<< orphan*/  M_SONAME ; 
 struct sockaddr* SA (struct sockaddr_storage*) ; 
 int /*<<< orphan*/  SAE_CONNID_ANY ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ UIO_MAXIOV ; 
 int /*<<< orphan*/  UIO_USERSPACE32 ; 
 int /*<<< orphan*/  UIO_USERSPACE64 ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 scalar_t__ USER_ADDR_NULL ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int connectitx (struct socket*,struct sockaddr*,struct sockaddr*,struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int copyin (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int copyin_user_iovec_array (scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct user_iovec*) ; 
 int copyout (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  file_drop (int) ; 
 int file_socket (int,struct socket**) ; 
 int getsockaddr (struct socket*,struct sockaddr**,scalar_t__,int,int) ; 
 int getsockaddr_s (struct socket*,struct sockaddr_storage*,scalar_t__,int,int) ; 
 int uio_calculateresid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uio_create (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_free (int /*<<< orphan*/ *) ; 
 struct user_iovec* uio_iovsaddr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
connectx_nocancel(struct proc *p, struct connectx_args *uap, int *retval)
{
#pragma unused(p, retval)
	struct sockaddr_storage ss, sd;
	struct sockaddr *src = NULL, *dst = NULL;
	struct socket *so;
	int error, error1, fd = uap->socket;
	boolean_t dgram;
	sae_connid_t cid = SAE_CONNID_ANY;
	struct user32_sa_endpoints ep32;
	struct user64_sa_endpoints ep64;
	struct user_sa_endpoints ep;
	user_ssize_t bytes_written = 0;
	struct user_iovec *iovp;
	uio_t auio = NULL;

	AUDIT_ARG(fd, uap->socket);
	error = file_socket(fd, &so);
	if (error != 0)
		return (error);
	if (so == NULL) {
		error = EBADF;
		goto out;
	}

	if (uap->endpoints == USER_ADDR_NULL) {
		error = EINVAL;
		goto out;
	}

	if (IS_64BIT_PROCESS(p)) {
		error = copyin(uap->endpoints, (caddr_t)&ep64, sizeof(ep64));
		if (error != 0)
			goto out;

		ep.sae_srcif = ep64.sae_srcif;
		ep.sae_srcaddr = ep64.sae_srcaddr;
		ep.sae_srcaddrlen = ep64.sae_srcaddrlen;
		ep.sae_dstaddr = ep64.sae_dstaddr;
		ep.sae_dstaddrlen = ep64.sae_dstaddrlen;
	} else {
		error = copyin(uap->endpoints, (caddr_t)&ep32, sizeof(ep32));
		if (error != 0)
			goto out;

		ep.sae_srcif = ep32.sae_srcif;
		ep.sae_srcaddr = ep32.sae_srcaddr;
		ep.sae_srcaddrlen = ep32.sae_srcaddrlen;
		ep.sae_dstaddr = ep32.sae_dstaddr;
		ep.sae_dstaddrlen = ep32.sae_dstaddrlen;
	}

	/*
	 * Ask getsockaddr{_s} to not translate AF_UNSPEC to AF_INET
	 * if this is a datagram socket; translate for other types.
	 */
	dgram = (so->so_type == SOCK_DGRAM);

	/* Get socket address now before we obtain socket lock */
	if (ep.sae_srcaddr != USER_ADDR_NULL) {
		if (ep.sae_srcaddrlen > sizeof (ss)) {
			error = getsockaddr(so, &src, ep.sae_srcaddr, ep.sae_srcaddrlen, dgram);
		} else {
			error = getsockaddr_s(so, &ss, ep.sae_srcaddr, ep.sae_srcaddrlen, dgram);
			if (error == 0)
				src = (struct sockaddr *)&ss;
		}

		if (error)
			goto out;
	}

	if (ep.sae_dstaddr == USER_ADDR_NULL) {
		error = EINVAL;
		goto out;
	}

	/* Get socket address now before we obtain socket lock */
	if (ep.sae_dstaddrlen > sizeof (sd)) {
		error = getsockaddr(so, &dst, ep.sae_dstaddr, ep.sae_dstaddrlen, dgram);
	} else {
		error = getsockaddr_s(so, &sd, ep.sae_dstaddr, ep.sae_dstaddrlen, dgram);
		if (error == 0)
			dst = (struct sockaddr *)&sd;
	}

	if (error)
		goto out;

	VERIFY(dst != NULL);

	if (uap->iov != USER_ADDR_NULL) {
		/* Verify range before calling uio_create() */
		if (uap->iovcnt <= 0 || uap->iovcnt > UIO_MAXIOV){
			error = EINVAL;
			goto out;
		}

		if (uap->len == USER_ADDR_NULL){
			error = EINVAL;
			goto out;
		}

		/* allocate a uio to hold the number of iovecs passed */
		auio = uio_create(uap->iovcnt, 0,
		    (IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32),
		    UIO_WRITE);

		if (auio == NULL) {
			error = ENOMEM;
			goto out;
		}

		/*
		 * get location of iovecs within the uio.
		 * then copyin the iovecs from user space.
		 */
		iovp = uio_iovsaddr(auio);
		if (iovp == NULL) {
			error = ENOMEM;
			goto out;
		}
		error = copyin_user_iovec_array(uap->iov,
			IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32,
			uap->iovcnt, iovp);
		if (error != 0)
			goto out;

		/* finish setup of uio_t */
		error = uio_calculateresid(auio);
		if (error != 0) {
			goto out;
		}
	}

	error = connectitx(so, src, dst, p, ep.sae_srcif, uap->associd,
	    &cid, auio, uap->flags, &bytes_written);
	if (error == ERESTART)
		error = EINTR;

	if (uap->len != USER_ADDR_NULL) {
		error1 = copyout(&bytes_written, uap->len, sizeof (uap->len));
		/* give precedence to connectitx errors */
		if ((error1 != 0) && (error == 0))
			error = error1;
	}

	if (uap->connid != USER_ADDR_NULL) {
		error1 = copyout(&cid, uap->connid, sizeof (cid));
		/* give precedence to connectitx errors */
		if ((error1 != 0) && (error == 0))
			error = error1;
	}
out:
	file_drop(fd);
	if (auio != NULL) {
		uio_free(auio);
	}
	if (src != NULL && src != SA(&ss))
		FREE(src, M_SONAME);
	if (dst != NULL && dst != SA(&sd))
		FREE(dst, M_SONAME);
	return (error);
}