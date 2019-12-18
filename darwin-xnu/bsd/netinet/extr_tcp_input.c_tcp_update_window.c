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
typedef  scalar_t__ u_int32_t ;
struct tcphdr {scalar_t__ th_seq; scalar_t__ th_ack; } ;
struct tcpcb {scalar_t__ snd_wl1; scalar_t__ snd_wl2; scalar_t__ snd_wnd; scalar_t__ max_sndwnd; TYPE_2__* t_inpcb; } ;
struct TYPE_6__ {int /*<<< orphan*/  tcps_rcvwinupd; } ;
struct TYPE_5__ {TYPE_1__* inp_socket; } ;
struct TYPE_4__ {int so_flags; } ;

/* Variables and functions */
 scalar_t__ SEQ_LT (scalar_t__,scalar_t__) ; 
 int SOF_MP_SUBFLOW ; 
 int TH_ACK ; 
 int /*<<< orphan*/  mptcp_update_window_wakeup (struct tcpcb*) ; 
 TYPE_3__ tcpstat ; 

__attribute__((used)) static inline bool
tcp_update_window(struct tcpcb *tp, int thflags, struct tcphdr * th,
    u_int32_t tiwin, int tlen)
{
	/* Don't look at the window if there is no ACK flag */
	if ((thflags & TH_ACK) &&
	    (SEQ_LT(tp->snd_wl1, th->th_seq) ||
	    (tp->snd_wl1 == th->th_seq && (SEQ_LT(tp->snd_wl2, th->th_ack) ||
	    (tp->snd_wl2 == th->th_ack && tiwin > tp->snd_wnd))))) {
		/* keep track of pure window updates */
		if (tlen == 0 &&
		    tp->snd_wl2 == th->th_ack && tiwin > tp->snd_wnd)
			tcpstat.tcps_rcvwinupd++;
		tp->snd_wnd = tiwin;
		tp->snd_wl1 = th->th_seq;
		tp->snd_wl2 = th->th_ack;
		if (tp->snd_wnd > tp->max_sndwnd)
			tp->max_sndwnd = tp->snd_wnd;

		if (tp->t_inpcb->inp_socket->so_flags & SOF_MP_SUBFLOW)
			mptcp_update_window_wakeup(tp);
		return (true);
	}
	return (false);
}