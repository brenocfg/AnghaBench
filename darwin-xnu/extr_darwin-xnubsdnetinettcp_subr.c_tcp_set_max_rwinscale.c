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
typedef  int uint32_t ;
struct tcpcb {int request_r_scale; } ;
struct TYPE_2__ {int sb_flags; int sb_hiwat; } ;
struct socket {TYPE_1__ so_rcv; } ;
struct ifnet {int if_eflags; } ;

/* Variables and functions */
 int IFEF_3CA ; 
 scalar_t__ IFNET_IS_CELLULAR (struct ifnet*) ; 
 int SB_USRSIZE ; 
 int TCP_MAXWIN ; 
 int TCP_MAX_WINSHIFT ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int tcp_autorcvbuf_max ; 
 int /*<<< orphan*/  tcp_do_rfc1323 ; 
 int /*<<< orphan*/  tcp_win_scale ; 

void
tcp_set_max_rwinscale(struct tcpcb *tp, struct socket *so, struct ifnet *ifp)
{
	uint32_t maxsockbufsize;
	uint32_t rcvbuf_max;

	if (!tcp_do_rfc1323) {
		tp->request_r_scale = 0;
		return;
	}

	/*
	 * When we start a connection and don't know about the interface, set
	 * the scaling factor simply to the max - we can always announce less.
	 */
	if (!ifp || (IFNET_IS_CELLULAR(ifp) && (ifp->if_eflags & IFEF_3CA)))
		rcvbuf_max = (tcp_autorcvbuf_max << 1);
	else
		rcvbuf_max = tcp_autorcvbuf_max;

	tp->request_r_scale = max(tcp_win_scale, tp->request_r_scale);
	maxsockbufsize = ((so->so_rcv.sb_flags & SB_USRSIZE) != 0) ?
		so->so_rcv.sb_hiwat : rcvbuf_max;

	while (tp->request_r_scale < TCP_MAX_WINSHIFT &&
		(TCP_MAXWIN << tp->request_r_scale) < maxsockbufsize)
		tp->request_r_scale++;
	tp->request_r_scale = min(tp->request_r_scale, TCP_MAX_WINSHIFT);

}