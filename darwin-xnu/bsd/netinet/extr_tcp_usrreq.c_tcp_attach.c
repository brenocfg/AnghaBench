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
struct tcpcb {int /*<<< orphan*/  t_state; } ;
struct TYPE_4__ {scalar_t__ sb_hiwat; scalar_t__ sb_preconn_hiwat; int sb_flags; } ;
struct TYPE_3__ {scalar_t__ sb_hiwat; int sb_flags; } ;
struct socket {int so_state; TYPE_2__ so_snd; TYPE_1__ so_rcv; } ;
struct proc {int dummy; } ;
struct inpcb {int in6p_hops; int /*<<< orphan*/  inp_vflag; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  INP_IPV4 ; 
 int /*<<< orphan*/  INP_IPV6 ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int SB_AUTOSIZE ; 
 int SB_USRSIZE ; 
 scalar_t__ SOCK_CHECK_DOM (struct socket*,int /*<<< orphan*/ ) ; 
 int SS_NOFDREF ; 
 int /*<<< orphan*/  TCPS_CLOSED ; 
 int /*<<< orphan*/  in6_pcbdetach (struct inpcb*) ; 
 int in_pcballoc (struct socket*,int /*<<< orphan*/ *,struct proc*) ; 
 int /*<<< orphan*/  in_pcbdetach (struct inpcb*) ; 
 scalar_t__ nstat_collect ; 
 int /*<<< orphan*/  nstat_tcp_new_pcb (struct inpcb*) ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soreserve_preconnect (struct socket*,int) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int /*<<< orphan*/  tcbinfo ; 
 struct tcpcb* tcp_newtcpcb (struct inpcb*) ; 
 int /*<<< orphan*/  tcp_recvspace ; 
 int /*<<< orphan*/  tcp_sendspace ; 

__attribute__((used)) static int
tcp_attach(struct socket *so, struct proc *p)
{
	struct tcpcb *tp;
	struct inpcb *inp;
	int error;
#if INET6
	int isipv6 = SOCK_CHECK_DOM(so, PF_INET6) != 0;
#endif

	error = in_pcballoc(so, &tcbinfo, p);
	if (error)
		return (error);

	inp = sotoinpcb(so);

	if (so->so_snd.sb_hiwat == 0 || so->so_rcv.sb_hiwat == 0) {
		error = soreserve(so, tcp_sendspace, tcp_recvspace);
		if (error)
			return (error);
	}

	if (so->so_snd.sb_preconn_hiwat == 0) {
		soreserve_preconnect(so, 2048);
	}

	if ((so->so_rcv.sb_flags & SB_USRSIZE) == 0)
		so->so_rcv.sb_flags |= SB_AUTOSIZE;
	if ((so->so_snd.sb_flags & SB_USRSIZE) == 0)
		so->so_snd.sb_flags |= SB_AUTOSIZE;

#if INET6
	if (isipv6) {
		inp->inp_vflag |= INP_IPV6;
		inp->in6p_hops = -1;	/* use kernel default */
	}
	else
#endif /* INET6 */
	inp->inp_vflag |= INP_IPV4;
	tp = tcp_newtcpcb(inp);
	if (tp == NULL) {
		int nofd = so->so_state & SS_NOFDREF;	/* XXX */

		so->so_state &= ~SS_NOFDREF;	/* don't free the socket yet */
#if INET6
		if (isipv6)
			in6_pcbdetach(inp);
		else
#endif /* INET6 */
		in_pcbdetach(inp);
		so->so_state |= nofd;
		return (ENOBUFS);
	}
	if (nstat_collect)
		nstat_tcp_new_pcb(inp);
	tp->t_state = TCPS_CLOSED;
	return (0);
}