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
typedef  scalar_t__ u_int64_t ;
typedef  scalar_t__ u_int32_t ;
struct tcphdr {int dummy; } ;
struct tcpcb {scalar_t__ t_bytes_acked; scalar_t__ snd_cwnd; int snd_scale; scalar_t__ t_maxseg; } ;

/* Variables and functions */
 scalar_t__ BYTES_ACKED (struct tcphdr*,struct tcpcb*) ; 
 scalar_t__ TCP_CUBIC_ENABLE_TCPMODE (struct tcpcb*) ; 
 int TCP_MAXWIN ; 
 scalar_t__ get_base_rtt (struct tcpcb*) ; 
 void* min (scalar_t__,int) ; 
 scalar_t__ tcp_cc_is_cwnd_nonvalidated (struct tcpcb*) ; 
 int tcp_cubic_tcp_friendliness ; 
 scalar_t__ tcp_cubic_tcpwin (struct tcpcb*,struct tcphdr*) ; 
 scalar_t__ tcp_cubic_update (struct tcpcb*,scalar_t__) ; 

__attribute__((used)) static void
tcp_cubic_congestion_avd(struct tcpcb *tp, struct tcphdr *th)
{
	u_int32_t cubic_target_win, tcp_win, rtt;

	/* Do not increase congestion window in non-validated phase */
	if (tcp_cc_is_cwnd_nonvalidated(tp) != 0)
		return;

	tp->t_bytes_acked += BYTES_ACKED(th, tp);

	rtt = get_base_rtt(tp);
	/*
	 * First compute cubic window. If cubic variables are not
	 * initialized (after coming out of recovery), this call will
	 * initialize them.
	 */
	cubic_target_win = tcp_cubic_update(tp, rtt);

	/* Compute TCP window if a multiplicative decrease of 0.2 is used */
	tcp_win = tcp_cubic_tcpwin(tp, th);

	if (tp->snd_cwnd < tcp_win &&
	    (tcp_cubic_tcp_friendliness == 1 ||
	    TCP_CUBIC_ENABLE_TCPMODE(tp))) {
		/* this connection is in TCP-friendly region */
		if (tp->t_bytes_acked >= tp->snd_cwnd) {
			tp->t_bytes_acked -= tp->snd_cwnd;
			tp->snd_cwnd = min(tcp_win, TCP_MAXWIN << tp->snd_scale);
		}
	} else {
		if (cubic_target_win > tp->snd_cwnd) {
			/*
			 * The target win is computed for the next RTT.
			 * To reach this value, cwnd will have to be updated
			 * one segment at a time. Compute how many bytes 
			 * need to be acknowledged before we can increase 
			 * the cwnd by one segment.
			 */
			u_int64_t incr_win;
			incr_win = tp->snd_cwnd * tp->t_maxseg;
			incr_win /= (cubic_target_win - tp->snd_cwnd);
			if (incr_win > 0 &&
			    tp->t_bytes_acked >= incr_win) {
				tp->t_bytes_acked -= incr_win;
				tp->snd_cwnd = 
				    min((tp->snd_cwnd + tp->t_maxseg),
				    TCP_MAXWIN << tp->snd_scale);
			}
		}
	}
}