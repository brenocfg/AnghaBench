#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int32_t ;
struct tcpcb {int rcv_adv; int rcv_nxt; int t_maxseg; } ;
struct sockbuf {scalar_t__ sb_idealsize; scalar_t__ sb_hiwat; scalar_t__ sb_cc; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ imin (scalar_t__,scalar_t__) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  sbreserve (struct sockbuf*,scalar_t__) ; 
 int tcp_autorcvbuf_inc_shift ; 
 int tcp_do_autorcvbuf ; 

void
tcp_sbrcv_trim(struct tcpcb *tp, struct sockbuf *sbrcv)
{
	if (tcp_do_autorcvbuf == 1 && sbrcv->sb_idealsize > 0 &&
		sbrcv->sb_hiwat > sbrcv->sb_idealsize) {
		int32_t trim;
		/* compute the difference between ideal and current sizes */
		u_int32_t diff = sbrcv->sb_hiwat - sbrcv->sb_idealsize;

		/* Compute the maximum advertised window for
		 * this connection.
		 */
		u_int32_t advwin = tp->rcv_adv - tp->rcv_nxt;

		/* How much can we trim the receive socket buffer?
		 * 1. it can not be trimmed beyond the max rcv win advertised
		 * 2. if possible, leave 1/16 of bandwidth*delay to
		 * avoid closing the win completely
		 */
		u_int32_t leave = max(advwin, (sbrcv->sb_idealsize >> 4));

		/* Sometimes leave can be zero, in that case leave at least
 		 * a few segments worth of space.
		 */
		if (leave == 0)
			leave = tp->t_maxseg << tcp_autorcvbuf_inc_shift;

		trim = sbrcv->sb_hiwat - (sbrcv->sb_cc + leave);
		trim = imin(trim, (int32_t)diff);

		if (trim > 0)
			sbreserve(sbrcv, (sbrcv->sb_hiwat - trim));
	}
}