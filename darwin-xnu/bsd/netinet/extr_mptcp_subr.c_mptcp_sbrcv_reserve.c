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
typedef  int uint8_t ;
typedef  scalar_t__ u_int32_t ;
struct sockbuf {scalar_t__ sb_hiwat; scalar_t__ sb_idealsize; } ;
struct mptcb {int /*<<< orphan*/  mpt_mpte; } ;

/* Variables and functions */
 int TCP_MAXWIN ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 void* min (scalar_t__,int) ; 
 int mptcp_get_rcvscale (int /*<<< orphan*/ ) ; 
 int sbreserve (struct sockbuf*,scalar_t__) ; 
 int tcp_autorcvbuf_max ; 

__attribute__((used)) static void
mptcp_sbrcv_reserve(struct mptcb *mp_tp, struct sockbuf *sbrcv,
	u_int32_t newsize, u_int32_t idealsize)
{
	uint8_t rcvscale = mptcp_get_rcvscale(mp_tp->mpt_mpte);

	/* newsize should not exceed max */
	newsize = min(newsize, tcp_autorcvbuf_max);

	/* The receive window scale negotiated at the
	 * beginning of the connection will also set a
	 * limit on the socket buffer size
	 */
	newsize = min(newsize, TCP_MAXWIN << rcvscale);

	/* Set new socket buffer size */
	if (newsize > sbrcv->sb_hiwat &&
		(sbreserve(sbrcv, newsize) == 1)) {
		sbrcv->sb_idealsize = min(max(sbrcv->sb_idealsize,
		    (idealsize != 0) ? idealsize : newsize), tcp_autorcvbuf_max);

		/* Again check the limit set by the advertised
		 * window scale
		 */
		sbrcv->sb_idealsize = min(sbrcv->sb_idealsize,
			TCP_MAXWIN << rcvscale);
	}
}