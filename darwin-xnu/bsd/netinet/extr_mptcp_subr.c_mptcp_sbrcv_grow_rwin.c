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
struct socket {int so_flags1; } ;
struct sockbuf {scalar_t__ sb_hiwat; scalar_t__ sb_cc; scalar_t__ sb_idealsize; } ;
struct mptcb {TYPE_2__* mpt_mpte; } ;
struct TYPE_4__ {TYPE_1__* mpte_mppcb; } ;
struct TYPE_3__ {struct socket* mpp_socket; } ;

/* Variables and functions */
 scalar_t__ IS_TCP_RECV_BG (struct socket*) ; 
 int SOF1_EXTEND_BK_IDLE_WANTED ; 
 int /*<<< orphan*/  min (scalar_t__,scalar_t__) ; 
 int mptcp_get_maxseg (TYPE_2__*) ; 
 int /*<<< orphan*/  sbreserve (struct sockbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_autorcvbuf_max ; 
 scalar_t__ tcp_cansbgrow (struct sockbuf*) ; 
 int tcp_do_autorcvbuf ; 
 int tcp_recv_bg ; 

__attribute__((used)) static void
mptcp_sbrcv_grow_rwin(struct mptcb *mp_tp, struct sockbuf *sb)
{
	struct socket *mp_so = mp_tp->mpt_mpte->mpte_mppcb->mpp_socket;
	u_int32_t rcvbufinc = mptcp_get_maxseg(mp_tp->mpt_mpte) << 4;
	u_int32_t rcvbuf = sb->sb_hiwat;

	if (tcp_recv_bg == 1 || IS_TCP_RECV_BG(mp_so))
		return;

	if (tcp_do_autorcvbuf == 1 &&
	    tcp_cansbgrow(sb) &&
	    /* Diff to tcp_sbrcv_grow_rwin */
	    (mp_so->so_flags1 & SOF1_EXTEND_BK_IDLE_WANTED) == 0 &&
	    (rcvbuf - sb->sb_cc) < rcvbufinc &&
	    rcvbuf < tcp_autorcvbuf_max &&
	    (sb->sb_idealsize > 0 &&
	    sb->sb_hiwat <= (sb->sb_idealsize + rcvbufinc))) {
		sbreserve(sb, min((sb->sb_hiwat + rcvbufinc), tcp_autorcvbuf_max));
	}
}