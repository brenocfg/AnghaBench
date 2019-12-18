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
typedef  int u64 ;
typedef  int u32 ;
struct veno {int cntrtt; int minrtt; int basertt; int diff; int inc; int /*<<< orphan*/  doing_veno_now; } ;
struct tcp_sock {int snd_cwnd; int snd_ssthresh; int snd_cwnd_cnt; int snd_cwnd_clamp; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int V_PARAM_SHIFT ; 
 int beta ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 struct veno* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  tcp_cong_avoid_ai (struct tcp_sock*,int) ; 
 int /*<<< orphan*/  tcp_is_cwnd_limited (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_reno_cong_avoid (struct sock*,int,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_slow_start (struct tcp_sock*) ; 

__attribute__((used)) static void tcp_veno_cong_avoid(struct sock *sk, u32 ack, u32 in_flight)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct veno *veno = inet_csk_ca(sk);

	if (!veno->doing_veno_now) {
		tcp_reno_cong_avoid(sk, ack, in_flight);
		return;
	}

	/* limited by applications */
	if (!tcp_is_cwnd_limited(sk, in_flight))
		return;

	/* We do the Veno calculations only if we got enough rtt samples */
	if (veno->cntrtt <= 2) {
		/* We don't have enough rtt samples to do the Veno
		 * calculation, so we'll behave like Reno.
		 */
		tcp_reno_cong_avoid(sk, ack, in_flight);
	} else {
		u64 target_cwnd;
		u32 rtt;

		/* We have enough rtt samples, so, using the Veno
		 * algorithm, we determine the state of the network.
		 */

		rtt = veno->minrtt;

		target_cwnd = (tp->snd_cwnd * veno->basertt);
		target_cwnd <<= V_PARAM_SHIFT;
		do_div(target_cwnd, rtt);

		veno->diff = (tp->snd_cwnd << V_PARAM_SHIFT) - target_cwnd;

		if (tp->snd_cwnd <= tp->snd_ssthresh) {
			/* Slow start.  */
			tcp_slow_start(tp);
		} else {
			/* Congestion avoidance. */
			if (veno->diff < beta) {
				/* In the "non-congestive state", increase cwnd
				 *  every rtt.
				 */
				tcp_cong_avoid_ai(tp, tp->snd_cwnd);
			} else {
				/* In the "congestive state", increase cwnd
				 * every other rtt.
				 */
				if (tp->snd_cwnd_cnt >= tp->snd_cwnd) {
					if (veno->inc
					    && tp->snd_cwnd <
					    tp->snd_cwnd_clamp) {
						tp->snd_cwnd++;
						veno->inc = 0;
					} else
						veno->inc = 1;
					tp->snd_cwnd_cnt = 0;
				} else
					tp->snd_cwnd_cnt++;
			}

		}
		if (tp->snd_cwnd < 2)
			tp->snd_cwnd = 2;
		else if (tp->snd_cwnd > tp->snd_cwnd_clamp)
			tp->snd_cwnd = tp->snd_cwnd_clamp;
	}
	/* Wipe the slate clean for the next rtt. */
	/* veno->cntrtt = 0; */
	veno->minrtt = 0x7fffffff;
}