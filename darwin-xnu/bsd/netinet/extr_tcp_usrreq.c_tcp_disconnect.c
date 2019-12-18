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
struct tcpcb {scalar_t__ t_reassqlen; scalar_t__ t_state; int t_mpflags; TYPE_1__* t_inpcb; } ;
struct TYPE_4__ {scalar_t__ sb_cc; } ;
struct socket {int so_options; scalar_t__ so_linger; int so_flags; TYPE_2__ so_rcv; } ;
struct TYPE_3__ {struct socket* inp_socket; } ;

/* Variables and functions */
 int SOF_MP_SUBFLOW ; 
 int SO_LINGER ; 
 scalar_t__ TCPS_ESTABLISHED ; 
 int TMPF_RESET ; 
 int /*<<< orphan*/  sbflush (TYPE_2__*) ; 
 int /*<<< orphan*/  soisdisconnecting (struct socket*) ; 
 struct tcpcb* tcp_close (struct tcpcb*) ; 
 struct tcpcb* tcp_drop (struct tcpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_output (struct tcpcb*) ; 
 struct tcpcb* tcp_usrclosed (struct tcpcb*) ; 

__attribute__((used)) static struct tcpcb *
tcp_disconnect(struct tcpcb *tp)
{
	struct socket *so = tp->t_inpcb->inp_socket;

	if (so->so_rcv.sb_cc != 0 || tp->t_reassqlen != 0)
		return tcp_drop(tp, 0);

	if (tp->t_state < TCPS_ESTABLISHED)
		tp = tcp_close(tp);
	else if ((so->so_options & SO_LINGER) && so->so_linger == 0)
		tp = tcp_drop(tp, 0);
	else {
		soisdisconnecting(so);
		sbflush(&so->so_rcv);
		tp = tcp_usrclosed(tp);
#if MPTCP
		/* A reset has been sent but socket exists, do not send FIN */
		if ((so->so_flags & SOF_MP_SUBFLOW) &&
		    (tp) && (tp->t_mpflags & TMPF_RESET))
			return (tp);
#endif
		if (tp)
			(void) tcp_output(tp);
	}
	return (tp);
}