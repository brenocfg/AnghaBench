#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_ssize_t ;
typedef  int /*<<< orphan*/  uio_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct uio {int dummy; } ;
struct socket {int so_flags1; TYPE_2__* so_proto; } ;
struct sockaddr {int dummy; } ;
struct proc {int dummy; } ;
struct inpcb {int inp_flags2; } ;
typedef  int sae_connid_t ;
typedef  int /*<<< orphan*/  sae_associd_t ;
struct TYPE_6__ {int /*<<< orphan*/  t_flagsext; } ;
struct TYPE_5__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_4__ {int (* pru_sosend ) (struct socket*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ASSERT (int) ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  IFSCOPE_NONE ; 
 int INP2_CONNECT_IN_PROGRESS ; 
 int SOF1_DATA_IDEMPOTENT ; 
 int SOF1_PRECONNECT_DATA ; 
 int TCP_FASTOPEN_CLIENT ; 
 int /*<<< orphan*/  TF_FASTOPEN ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int inp_bindif (struct inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inp_update_necp_policy (struct inpcb*,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int sobindlock (struct socket*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 TYPE_3__* sototcpcb (struct socket*) ; 
 int stub1 (struct socket*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tcp6_usr_connect (struct socket*,struct sockaddr*,struct proc*) ; 
 int tcp_fastopen ; 
 int tcp_usr_connect (struct socket*,struct sockaddr*,struct proc*) ; 
 scalar_t__ uio_resid (struct uio*) ; 

__attribute__((used)) static int
tcp_usr_connectx_common(struct socket *so, int af,
    struct sockaddr *src, struct sockaddr *dst,
    struct proc *p, uint32_t ifscope, sae_associd_t aid, sae_connid_t *pcid,
    uint32_t flags, void *arg, uint32_t arglen, struct uio *auio,
    user_ssize_t *bytes_written)
{
#pragma unused(aid, flags, arg, arglen)
	struct inpcb *inp = sotoinpcb(so);
	int error = 0;
	user_ssize_t datalen = 0;

	if (inp == NULL)
		return (EINVAL);

	VERIFY(dst != NULL);

	ASSERT(!(inp->inp_flags2 & INP2_CONNECT_IN_PROGRESS));
	inp->inp_flags2 |= INP2_CONNECT_IN_PROGRESS;

#if NECP
	inp_update_necp_policy(inp, src, dst, ifscope);
#endif /* NECP */

	if ((so->so_flags1 & SOF1_DATA_IDEMPOTENT) &&
	    (tcp_fastopen & TCP_FASTOPEN_CLIENT))
		sototcpcb(so)->t_flagsext |= TF_FASTOPEN;

	/* bind socket to the specified interface, if requested */
	if (ifscope != IFSCOPE_NONE &&
		(error = inp_bindif(inp, ifscope, NULL)) != 0) {
		goto done;
	}

	/* if source address and/or port is specified, bind to it */
	if (src != NULL) {
		error = sobindlock(so, src, 0);	/* already locked */
		if (error != 0) {
			goto done;
		}
	}

	switch (af) {
	case AF_INET:
		error = tcp_usr_connect(so, dst, p);
		break;
#if INET6
	case AF_INET6:
		error = tcp6_usr_connect(so, dst, p);
		break;
#endif /* INET6 */
	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	if (error != 0) {
		goto done;
	}

	/* if there is data, copy it */
	if (auio != NULL) {
		socket_unlock(so, 0);

		VERIFY(bytes_written != NULL);

		datalen = uio_resid(auio);
		error = so->so_proto->pr_usrreqs->pru_sosend(so, NULL,
	            (uio_t)auio, NULL, NULL, 0);
		socket_lock(so, 0);

		if (error == 0 || error == EWOULDBLOCK)
			*bytes_written = datalen - uio_resid(auio);

		/*
		 * sosend returns EWOULDBLOCK if it's a non-blocking
		 * socket or a timeout occured (this allows to return
		 * the amount of queued data through sendit()).
		 *
		 * However, connectx() returns EINPROGRESS in case of a
		 * blocking socket. So we change the return value here.
		 */
		if (error == EWOULDBLOCK)
			error = EINPROGRESS;
	}

	if (error == 0 && pcid != NULL)
		*pcid = 1; /* there is only one connection in regular TCP */

done:
	if (error && error != EINPROGRESS)
		so->so_flags1 &= ~SOF1_PRECONNECT_DATA;

	inp->inp_flags2 &= ~INP2_CONNECT_IN_PROGRESS;
	return (error);
}