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
struct tcphdr {int dummy; } ;
struct tcpcb {scalar_t__ snd_cwnd; scalar_t__ snd_ssthresh; scalar_t__ snd_nxt; scalar_t__ snd_max; int t_maxseg; int snd_scale; } ;

/* Variables and functions */
 int BYTES_ACKED (struct tcphdr*,struct tcpcb*) ; 
 int TCP_MAXWIN ; 
 void* min (int,int) ; 
 scalar_t__ tcp_cc_is_cwnd_nonvalidated (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_cubic_congestion_avd (struct tcpcb*,struct tcphdr*) ; 
 scalar_t__ tcp_do_rfc3465_lim2 ; 

__attribute__((used)) static void
tcp_cubic_ack_rcvd(struct tcpcb *tp, struct tcphdr *th)
{
	/* Do not increase the congestion window in non-validated phase */
	if (tcp_cc_is_cwnd_nonvalidated(tp) != 0)
		return;

	if (tp->snd_cwnd >= tp->snd_ssthresh) {
		/* Congestion avoidance phase */
		tcp_cubic_congestion_avd(tp, th);
	} else {
		/*
		 * Use 2*SMSS as limit on increment as suggested
		 * by RFC 3465 section 2.3
		 */
		uint32_t acked, abc_lim, incr;

		acked = BYTES_ACKED(th, tp);
		abc_lim = (tcp_do_rfc3465_lim2 && 
			tp->snd_nxt == tp->snd_max) ?
			2 * tp->t_maxseg : tp->t_maxseg;
		incr = min(acked, abc_lim);

		tp->snd_cwnd += incr;
		tp->snd_cwnd = min(tp->snd_cwnd, 
			TCP_MAXWIN << tp->snd_scale);
	}
}