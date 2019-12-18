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
typedef  scalar_t__ u_int32_t ;
struct tcpcb {scalar_t__ rcv_scale; } ;
struct sockbuf {scalar_t__ sb_hiwat; scalar_t__ sb_idealsize; } ;

/* Variables and functions */
 scalar_t__ TCP_MAXWIN ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 void* min (scalar_t__,scalar_t__) ; 
 int sbreserve (struct sockbuf*,scalar_t__) ; 

__attribute__((used)) static void
tcp_sbrcv_reserve(struct tcpcb *tp, struct sockbuf *sbrcv,
	u_int32_t newsize, u_int32_t idealsize, u_int32_t rcvbuf_max)
{
	/* newsize should not exceed max */
	newsize = min(newsize, rcvbuf_max);

	/* The receive window scale negotiated at the
	 * beginning of the connection will also set a
	 * limit on the socket buffer size
	 */
	newsize = min(newsize, TCP_MAXWIN << tp->rcv_scale);

	/* Set new socket buffer size */
	if (newsize > sbrcv->sb_hiwat &&
		(sbreserve(sbrcv, newsize) == 1)) {
		sbrcv->sb_idealsize = min(max(sbrcv->sb_idealsize,
		    (idealsize != 0) ? idealsize : newsize), rcvbuf_max);

		/* Again check the limit set by the advertised
		 * window scale
		 */
		sbrcv->sb_idealsize = min(sbrcv->sb_idealsize,
			TCP_MAXWIN << tp->rcv_scale);
	}
}