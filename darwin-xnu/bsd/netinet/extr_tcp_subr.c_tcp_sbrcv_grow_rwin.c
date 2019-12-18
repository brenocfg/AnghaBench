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
typedef  scalar_t__ u_int32_t ;
struct tcpcb {int t_maxseg; int t_flags; TYPE_1__* t_inpcb; } ;
struct socket {int so_flags; int so_flags1; TYPE_2__* so_msg_state; } ;
struct sockbuf {scalar_t__ sb_hiwat; scalar_t__ sb_cc; scalar_t__ sb_idealsize; } ;
struct TYPE_4__ {scalar_t__ msg_uno_bytes; } ;
struct TYPE_3__ {struct socket* inp_socket; } ;

/* Variables and functions */
 scalar_t__ IS_TCP_RECV_BG (struct socket*) ; 
 int SOF1_EXTEND_BK_IDLE_WANTED ; 
 int SOF_ENABLE_MSGS ; 
 int TF_SLOWLINK ; 
 int /*<<< orphan*/  min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sbreserve (struct sockbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_autorcvbuf_max ; 
 scalar_t__ tcp_cansbgrow (struct sockbuf*) ; 
 int tcp_do_autorcvbuf ; 
 int tcp_recv_bg ; 

__attribute__((used)) static void
tcp_sbrcv_grow_rwin(struct tcpcb *tp, struct sockbuf *sb)
{
	u_int32_t rcvbufinc = tp->t_maxseg << 4;
	u_int32_t rcvbuf = sb->sb_hiwat;
	struct socket *so = tp->t_inpcb->inp_socket;

	if (tcp_recv_bg == 1 || IS_TCP_RECV_BG(so))
		return;
	/*
	 * If message delivery is enabled, do not count
	 * unordered bytes in receive buffer towards hiwat
	 */
	if (so->so_flags & SOF_ENABLE_MSGS)
		rcvbuf = rcvbuf - so->so_msg_state->msg_uno_bytes;

	if (tcp_do_autorcvbuf == 1 &&
		tcp_cansbgrow(sb) &&
		(tp->t_flags & TF_SLOWLINK) == 0 &&
		(so->so_flags1 & SOF1_EXTEND_BK_IDLE_WANTED) == 0 &&
		(rcvbuf - sb->sb_cc) < rcvbufinc &&
		rcvbuf < tcp_autorcvbuf_max &&
		(sb->sb_idealsize > 0 &&
		sb->sb_hiwat <= (sb->sb_idealsize + rcvbufinc))) {
		sbreserve(sb,
		    min((sb->sb_hiwat + rcvbufinc), tcp_autorcvbuf_max));
	}
}