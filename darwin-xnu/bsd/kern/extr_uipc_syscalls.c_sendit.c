#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_ssize_t ;
typedef  int /*<<< orphan*/  uio_t ;
struct user_msghdr {int msg_namelen; int msg_controllen; int /*<<< orphan*/  msg_control; int /*<<< orphan*/  msg_name; } ;
struct socket {int so_state; int so_flags; TYPE_2__* so_proto; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct proc {int dummy; } ;
struct mbuf {int dummy; } ;
struct cmsghdr {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int int32_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_3__ {int (* pru_sosend ) (struct socket*,struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*) ; 
 int DBG_FNC_SENDIT ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int EINTR ; 
 int EINVAL ; 
 int EPIPE ; 
 int ERESTART ; 
 int EWOULDBLOCK ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FREE (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_CONTROL ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int SOF_NOSIGPIPE ; 
 int SS_DEFUNCT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int getsockaddr (struct socket*,struct sockaddr**,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int getsockaddr_s (struct socket*,struct sockaddr_storage*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int mac_socket_check_send (int /*<<< orphan*/ ,struct socket*,struct sockaddr*) ; 
 int /*<<< orphan*/  psignal (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sockaddr ; 
 int sockargs (struct mbuf**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct socket*,struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,int) ; 
 scalar_t__ uio_resid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int /*<<< orphan*/  vfs_context_cwd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sendit(struct proc *p, struct socket *so, struct user_msghdr *mp, uio_t uiop,
    int flags, int32_t *retval)
{
	struct mbuf *control = NULL;
	struct sockaddr_storage ss;
	struct sockaddr *to = NULL;
	boolean_t want_free = TRUE;
	int error;
	user_ssize_t len;

	KERNEL_DEBUG(DBG_FNC_SENDIT | DBG_FUNC_START, 0, 0, 0, 0, 0);

	if (mp->msg_name != USER_ADDR_NULL) {
		if (mp->msg_namelen > sizeof (ss)) {
			error = getsockaddr(so, &to, mp->msg_name,
			    mp->msg_namelen, TRUE);
		} else {
			error = getsockaddr_s(so, &ss, mp->msg_name,
			    mp->msg_namelen, TRUE);
			if (error == 0) {
				to = (struct sockaddr *)&ss;
				want_free = FALSE;
			}
		}
		if (error != 0)
			goto out;
		AUDIT_ARG(sockaddr, vfs_context_cwd(vfs_context_current()), to);
	}
	if (mp->msg_control != USER_ADDR_NULL) {
		if (mp->msg_controllen < sizeof (struct cmsghdr)) {
			error = EINVAL;
			goto bad;
		}
		error = sockargs(&control, mp->msg_control,
		    mp->msg_controllen, MT_CONTROL);
		if (error != 0)
			goto bad;
	}

#if CONFIG_MACF_SOCKET_SUBSET
	/*
	 * We check the state without holding the socket lock;
	 * if a race condition occurs, it would simply result
	 * in an extra call to the MAC check function.
	 */
	if (to != NULL &&
	    !(so->so_state & SS_DEFUNCT) &&
	    (error = mac_socket_check_send(kauth_cred_get(), so, to)) != 0)
		goto bad;
#endif /* MAC_SOCKET_SUBSET */

	len = uio_resid(uiop);
	error = so->so_proto->pr_usrreqs->pru_sosend(so, to, uiop, 0,
		control, flags);
	if (error != 0) {
		if (uio_resid(uiop) != len && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
		/* Generation of SIGPIPE can be controlled per socket */
		if (error == EPIPE && !(so->so_flags & SOF_NOSIGPIPE))
			psignal(p, SIGPIPE);
	}
	if (error == 0)
		*retval = (int)(len - uio_resid(uiop));
bad:
	if (to != NULL && want_free)
		FREE(to, M_SONAME);
out:
	KERNEL_DEBUG(DBG_FNC_SENDIT | DBG_FUNC_END, error, 0, 0, 0, 0);

	return (error);
}