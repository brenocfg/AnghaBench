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
typedef  scalar_t__ u_int ;
struct tcphdr {int dummy; } ;
struct tcpcb {scalar_t__ snd_cwnd; scalar_t__ t_maxseg; scalar_t__ t_bytes_acked; scalar_t__ bg_ssthresh; scalar_t__ snd_nxt; scalar_t__ snd_max; } ;

/* Variables and functions */
 int BYTES_ACKED (struct tcphdr*,struct tcpcb*) ; 
 scalar_t__ lmin (int,scalar_t__) ; 
 scalar_t__ tcp_do_rfc3465_lim2 ; 
 int /*<<< orphan*/  update_cwnd (struct tcpcb*,scalar_t__) ; 

void
tcp_ledbat_ack_rcvd(struct tcpcb *tp, struct tcphdr *th) {
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
	tp->t_bytes_acked += acked;
	if (cw >= tp->bg_ssthresh) {
		/* congestion-avoidance */
		if (tp->t_bytes_acked < cw) {
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
		u_int abc_lim;

		abc_lim = (tcp_do_rfc3465_lim2 &&
			tp->snd_nxt == tp->snd_max) ? incr * 2 : incr;

		incr = lmin(acked, abc_lim);
	}
	if (tp->t_bytes_acked >= cw)
		tp->t_bytes_acked -= cw;
	if (incr > 0) 
		update_cwnd(tp, incr);
}