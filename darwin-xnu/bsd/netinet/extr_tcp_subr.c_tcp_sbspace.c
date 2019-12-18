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
struct tcpcb {scalar_t__ t_maxseg; int t_flags; TYPE_1__* t_inpcb; } ;
struct sockbuf {scalar_t__ sb_hiwat; scalar_t__ sb_cc; scalar_t__ sb_mbmax; scalar_t__ sb_mbcnt; } ;
struct socket {int so_flags; TYPE_2__* so_msg_state; struct sockbuf so_rcv; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {scalar_t__ msg_uno_bytes; } ;
struct TYPE_3__ {struct socket* inp_socket; } ;

/* Variables and functions */
 int SOF_ENABLE_MSGS ; 
 int TF_SLOWLINK ; 
 scalar_t__ cfil_sock_data_space (struct sockbuf*) ; 
 scalar_t__ imin (scalar_t__,scalar_t__) ; 
 scalar_t__ slowlink_wsize ; 
 int /*<<< orphan*/  tcp_sbrcv_grow_rwin (struct tcpcb*,struct sockbuf*) ; 

int32_t
tcp_sbspace(struct tcpcb *tp)
{
	struct socket *so = tp->t_inpcb->inp_socket;
	struct sockbuf *sb = &so->so_rcv;
	u_int32_t rcvbuf;
	int32_t space;
	int32_t pending = 0;

	tcp_sbrcv_grow_rwin(tp, sb);

	/* hiwat might have changed */
	rcvbuf = sb->sb_hiwat;

	/*
	 * If message delivery is enabled, do not count
	 * unordered bytes in receive buffer towards hiwat mark.
	 * This value is used to return correct rwnd that does
	 * not reflect the extra unordered bytes added to the
	 * receive socket buffer.
	 */
	if (so->so_flags & SOF_ENABLE_MSGS)
		rcvbuf = rcvbuf - so->so_msg_state->msg_uno_bytes;

	space =  ((int32_t) imin((rcvbuf - sb->sb_cc),
		(sb->sb_mbmax - sb->sb_mbcnt)));
	if (space < 0)
		space = 0;

#if CONTENT_FILTER
	/* Compensate for data being processed by content filters */
	pending = cfil_sock_data_space(sb);
#endif /* CONTENT_FILTER */
	if (pending > space)
		space = 0;
	else
		space -= pending;

	/*
	 * Avoid increasing window size if the current window
	 * is already very low, we could be in "persist" mode and
	 * we could break some apps (see rdar://5409343)
	 */

	if (space < tp->t_maxseg)
		return (space);

	/* Clip window size for slower link */

	if (((tp->t_flags & TF_SLOWLINK) != 0) && slowlink_wsize > 0)
		return (imin(space, slowlink_wsize));

	return (space);
}