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
typedef  int /*<<< orphan*/  uint32_t ;
struct uio {int dummy; } ;
struct socket {TYPE_2__* so_proto; } ;
struct sockaddr {int dummy; } ;
struct proc {int dummy; } ;
struct inpcb {int inp_flags2; } ;
typedef  int sae_connid_t ;
typedef  int /*<<< orphan*/  sae_associd_t ;
struct TYPE_4__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_3__ {int (* pru_sosend ) (struct socket*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pru_disconnectx ) (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ASSERT (int) ; 
 int EINVAL ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  IFSCOPE_NONE ; 
 int INP2_CONNECT_IN_PROGRESS ; 
 int /*<<< orphan*/  SAE_ASSOCID_ANY ; 
 int /*<<< orphan*/  SAE_CONNID_ANY ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int inp_bindif (struct inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inp_update_necp_policy (struct inpcb*,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int sobindlock (struct socket*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int stub1 (struct socket*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int udp6_connect (struct socket*,struct sockaddr*,struct proc*) ; 
 int udp_connect (struct socket*,struct sockaddr*,struct proc*) ; 
 scalar_t__ uio_resid (struct uio*) ; 

int
udp_connectx_common(struct socket *so, int af, struct sockaddr *src, struct sockaddr *dst,
    struct proc *p, uint32_t ifscope, sae_associd_t aid, sae_connid_t *pcid,
    uint32_t flags, void *arg, uint32_t arglen,
    struct uio *uio, user_ssize_t *bytes_written)
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
		error = udp_connect(so, dst, p);
		break;
#if INET6
	case AF_INET6:
		error = udp6_connect(so, dst, p);
		break;
#endif /* INET6 */
	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	if (error != 0) {
		goto done;
	}

	/*
	 * If there is data, copy it. DATA_IDEMPOTENT is ignored.
	 * CONNECT_RESUME_ON_READ_WRITE is ignored.
	 */
	if (uio != NULL) {
		socket_unlock(so, 0);

		VERIFY(bytes_written != NULL);

		datalen = uio_resid(uio);
		error = so->so_proto->pr_usrreqs->pru_sosend(so, NULL,
		    (uio_t)uio, NULL, NULL, 0);
		socket_lock(so, 0);

		/* If error returned is EMSGSIZE, for example, disconnect */
		if (error == 0 || error == EWOULDBLOCK)
			*bytes_written = datalen - uio_resid(uio);
		else
			(void) so->so_proto->pr_usrreqs->pru_disconnectx(so,
			    SAE_ASSOCID_ANY, SAE_CONNID_ANY);
		/*
		 * mask the EWOULDBLOCK error so that the caller
		 * knows that atleast the connect was successful.
		 */
		if (error == EWOULDBLOCK)
			error = 0;
	}

	if (error == 0 && pcid != NULL)
		*pcid = 1;	/* there is only 1 connection for UDP */

done:
	inp->inp_flags2 &= ~INP2_CONNECT_IN_PROGRESS;
	return (error);
}