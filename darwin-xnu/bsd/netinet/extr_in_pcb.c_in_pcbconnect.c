#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {int so_flags; int /*<<< orphan*/  so_state_change_cnt; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct proc {int dummy; } ;
struct in_addr {scalar_t__ s_addr; } ;
struct inpcb {scalar_t__ inp_lport; TYPE_1__* inp_pcbinfo; int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  inp_faddr; int /*<<< orphan*/  inp_flags; struct ifnet* inp_last_outifp; struct in_addr inp_laddr; struct socket* inp_socket; } ;
struct ifnet {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ipi_lock; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int ECONNREFUSED ; 
 int EINVAL ; 
 scalar_t__ INADDR_ANY ; 
 int /*<<< orphan*/  INP_INADDR_ANY ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ SOCK_PROTO (struct socket*) ; 
 int SOF_ABORTED ; 
 int /*<<< orphan*/  WNT_RELEASE ; 
 int /*<<< orphan*/  in_pcb_checkstate (struct inpcb*,int /*<<< orphan*/ ,int) ; 
 int in_pcbbind (struct inpcb*,int /*<<< orphan*/ *,struct proc*) ; 
 int in_pcbladdr (struct inpcb*,struct sockaddr*,struct in_addr*,unsigned int,struct ifnet**,int /*<<< orphan*/ ) ; 
 struct inpcb* in_pcblookup_hash (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in_addr,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_pcbrehash (struct inpcb*) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_try_lock_exclusive (int /*<<< orphan*/ ) ; 
 scalar_t__ nstat_collect ; 
 int /*<<< orphan*/  nstat_pcb_invalidate_cache (struct inpcb*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 

int
in_pcbconnect(struct inpcb *inp, struct sockaddr *nam, struct proc *p,
    unsigned int ifscope, struct ifnet **outif)
{
	struct in_addr laddr;
	struct sockaddr_in *sin = (struct sockaddr_in *)(void *)nam;
	struct inpcb *pcb;
	int error;
	struct socket *so = inp->inp_socket;

#if CONTENT_FILTER
	if (so)
		so->so_state_change_cnt++;
#endif

	/*
	 *   Call inner routine, to assign local interface address.
	 */
	if ((error = in_pcbladdr(inp, nam, &laddr, ifscope, outif, 0)) != 0)
		return (error);

	socket_unlock(so, 0);
	pcb = in_pcblookup_hash(inp->inp_pcbinfo, sin->sin_addr, sin->sin_port,
	    inp->inp_laddr.s_addr ? inp->inp_laddr : laddr,
	    inp->inp_lport, 0, NULL);
	socket_lock(so, 0);

	/*
	 * Check if the socket is still in a valid state. When we unlock this
	 * embryonic socket, it can get aborted if another thread is closing
	 * the listener (radar 7947600).
	 */
	if ((so->so_flags & SOF_ABORTED) != 0)
		return (ECONNREFUSED);

	if (pcb != NULL) {
		in_pcb_checkstate(pcb, WNT_RELEASE, pcb == inp ? 1 : 0);
		return (EADDRINUSE);
	}
	if (inp->inp_laddr.s_addr == INADDR_ANY) {
		if (inp->inp_lport == 0) {
			error = in_pcbbind(inp, NULL, p);
			if (error)
				return (error);
		}
		if (!lck_rw_try_lock_exclusive(inp->inp_pcbinfo->ipi_lock)) {
			/*
			 * Lock inversion issue, mostly with udp
			 * multicast packets.
			 */
			socket_unlock(so, 0);
			lck_rw_lock_exclusive(inp->inp_pcbinfo->ipi_lock);
			socket_lock(so, 0);
		}
		inp->inp_laddr = laddr;
		/* no reference needed */
		inp->inp_last_outifp = (outif != NULL) ? *outif : NULL;
		inp->inp_flags |= INP_INADDR_ANY;
	} else {
		/*
		 * Usage of IP_PKTINFO, without local port already
		 * speficified will cause kernel to panic,
		 * see rdar://problem/18508185.
		 * For now returning error to avoid a kernel panic
		 * This routines can be refactored and handle this better
		 * in future.
		 */
		if (inp->inp_lport == 0)
			return (EINVAL);
		if (!lck_rw_try_lock_exclusive(inp->inp_pcbinfo->ipi_lock)) {
			/*
			 * Lock inversion issue, mostly with udp
			 * multicast packets.
			 */
			socket_unlock(so, 0);
			lck_rw_lock_exclusive(inp->inp_pcbinfo->ipi_lock);
			socket_lock(so, 0);
		}
	}
	inp->inp_faddr = sin->sin_addr;
	inp->inp_fport = sin->sin_port;
	if (nstat_collect && SOCK_PROTO(so) == IPPROTO_UDP)
		nstat_pcb_invalidate_cache(inp);
	in_pcbrehash(inp);
	lck_rw_done(inp->inp_pcbinfo->ipi_lock);
	return (0);
}