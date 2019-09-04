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
typedef  int uint32_t ;
typedef  int u_int ;
struct tcphdr {int dummy; } ;
struct tcpcb {int snd_cwnd; int t_maxseg; int snd_ssthresh; int t_bytes_acked; scalar_t__ snd_nxt; scalar_t__ snd_max; int snd_scale; } ;

/* Variables and functions */
 int BYTES_ACKED (struct tcphdr*,struct tcpcb*) ; 
 int TCP_MAXWIN ; 
 int lmin (int,int) ; 
 int max (int,int) ; 
 int min (int,int) ; 
 scalar_t__ tcp_do_rfc3465 ; 
 scalar_t__ tcp_do_rfc3465_lim2 ; 

void
tcp_newreno_ack_rcvd(struct tcpcb *tp, struct tcphdr *th) {
	/*
	 * RFC 3465 - Appropriate Byte Counting.
	 *
	 * If the window is currently less than ssthresh,
	 * open the window by the number of bytes ACKed by
	 * the last ACK, however clamp the window increase
	 * to an upper limit "L".
	 *
	 * In congestion avoidance phase, open the window by
	 * one segment each time "bytes_acked" grows to be
	 * greater than or equal to the congestion window.
	 */

	u_int cw = tp->snd_cwnd;
	u_int incr = tp->t_maxseg;
	int acked = 0;

	acked = BYTES_ACKED(th, tp);
	if (tcp_do_rfc3465) {

		if (cw >= tp->snd_ssthresh) {
			tp->t_bytes_acked += acked;
			if (tp->t_bytes_acked >= cw) {
				/* Time to increase the window. */
				tp->t_bytes_acked -= cw;
			} else {
				/* No need to increase yet. */
				incr = 0;
			}
		} else {
			/*
			 * If the user explicitly enables RFC3465
			 * use 2*SMSS for the "L" param.  Otherwise
			 * use the more conservative 1*SMSS.
			 *
			 * (See RFC 3465 2.3 Choosing the Limit)
			 */
			uint32_t abc_lim;
			abc_lim = (tcp_do_rfc3465_lim2 &&
				tp->snd_nxt == tp->snd_max) ? incr * 2 
				: incr;

			incr = lmin(acked, abc_lim);
		}
	} else {
		/*
		 * If the window gives us less than ssthresh packets
		 * in flight, open exponentially (segsz per packet).
		 * Otherwise open linearly: segsz per window
		 * (segsz^2 / cwnd per packet).
		 */

		if (cw >= tp->snd_ssthresh)
			incr = max((incr * incr / cw), 1);
	}
	tp->snd_cwnd = min(cw+incr, TCP_MAXWIN<<tp->snd_scale);
}