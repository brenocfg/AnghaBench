#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int cntRTT; int minRTT; int baseRTT; int beg_snd_cwnd; int /*<<< orphan*/  beg_snd_nxt; int /*<<< orphan*/  beg_snd_una; } ;
struct yeah {int doing_reno_now; int pkts_acked; scalar_t__ reno_count; scalar_t__ fast_count; int lastQ; TYPE_1__ vegas; } ;
struct tcp_sock {scalar_t__ snd_cwnd; scalar_t__ snd_ssthresh; void* snd_cwnd_cnt; scalar_t__ snd_cwnd_clamp; int /*<<< orphan*/  snd_nxt; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int TCP_SCALABLE_AI_CNT ; 
 int TCP_YEAH_ALPHA ; 
 int TCP_YEAH_EPSILON ; 
 int TCP_YEAH_GAMMA ; 
 int TCP_YEAH_PHY ; 
 scalar_t__ TCP_YEAH_ZETA ; 
 scalar_t__ after (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 struct yeah* inet_csk_ca (struct sock*) ; 
 void* max (int,unsigned int) ; 
 void* min (int,int) ; 
 int /*<<< orphan*/  tcp_cong_avoid_ai (struct tcp_sock*,scalar_t__) ; 
 int /*<<< orphan*/  tcp_is_cwnd_limited (struct sock*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_slow_start (struct tcp_sock*) ; 

__attribute__((used)) static void tcp_yeah_cong_avoid(struct sock *sk, u32 ack, u32 in_flight)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct yeah *yeah = inet_csk_ca(sk);

	if (!tcp_is_cwnd_limited(sk, in_flight))
		return;

	if (tp->snd_cwnd <= tp->snd_ssthresh)
		tcp_slow_start(tp);

	else if (!yeah->doing_reno_now) {
		/* Scalable */

		tp->snd_cwnd_cnt += yeah->pkts_acked;
		if (tp->snd_cwnd_cnt > min(tp->snd_cwnd, TCP_SCALABLE_AI_CNT)){
			if (tp->snd_cwnd < tp->snd_cwnd_clamp)
				tp->snd_cwnd++;
			tp->snd_cwnd_cnt = 0;
		}

		yeah->pkts_acked = 1;

	} else {
		/* Reno */
		tcp_cong_avoid_ai(tp, tp->snd_cwnd);
	}

	/* The key players are v_vegas.beg_snd_una and v_beg_snd_nxt.
	 *
	 * These are so named because they represent the approximate values
	 * of snd_una and snd_nxt at the beginning of the current RTT. More
	 * precisely, they represent the amount of data sent during the RTT.
	 * At the end of the RTT, when we receive an ACK for v_beg_snd_nxt,
	 * we will calculate that (v_beg_snd_nxt - v_vegas.beg_snd_una) outstanding
	 * bytes of data have been ACKed during the course of the RTT, giving
	 * an "actual" rate of:
	 *
	 *     (v_beg_snd_nxt - v_vegas.beg_snd_una) / (rtt duration)
	 *
	 * Unfortunately, v_vegas.beg_snd_una is not exactly equal to snd_una,
	 * because delayed ACKs can cover more than one segment, so they
	 * don't line up yeahly with the boundaries of RTTs.
	 *
	 * Another unfortunate fact of life is that delayed ACKs delay the
	 * advance of the left edge of our send window, so that the number
	 * of bytes we send in an RTT is often less than our cwnd will allow.
	 * So we keep track of our cwnd separately, in v_beg_snd_cwnd.
	 */

	if (after(ack, yeah->vegas.beg_snd_nxt)) {

		/* We do the Vegas calculations only if we got enough RTT
		 * samples that we can be reasonably sure that we got
		 * at least one RTT sample that wasn't from a delayed ACK.
		 * If we only had 2 samples total,
		 * then that means we're getting only 1 ACK per RTT, which
		 * means they're almost certainly delayed ACKs.
		 * If  we have 3 samples, we should be OK.
		 */

		if (yeah->vegas.cntRTT > 2) {
			u32 rtt, queue;
			u64 bw;

			/* We have enough RTT samples, so, using the Vegas
			 * algorithm, we determine if we should increase or
			 * decrease cwnd, and by how much.
			 */

			/* Pluck out the RTT we are using for the Vegas
			 * calculations. This is the min RTT seen during the
			 * last RTT. Taking the min filters out the effects
			 * of delayed ACKs, at the cost of noticing congestion
			 * a bit later.
			 */
			rtt = yeah->vegas.minRTT;

			/* Compute excess number of packets above bandwidth
			 * Avoid doing full 64 bit divide.
			 */
			bw = tp->snd_cwnd;
			bw *= rtt - yeah->vegas.baseRTT;
			do_div(bw, rtt);
			queue = bw;

			if (queue > TCP_YEAH_ALPHA ||
			    rtt - yeah->vegas.baseRTT > (yeah->vegas.baseRTT / TCP_YEAH_PHY)) {
				if (queue > TCP_YEAH_ALPHA
				    && tp->snd_cwnd > yeah->reno_count) {
					u32 reduction = min(queue / TCP_YEAH_GAMMA ,
							    tp->snd_cwnd >> TCP_YEAH_EPSILON);

					tp->snd_cwnd -= reduction;

					tp->snd_cwnd = max(tp->snd_cwnd,
							   yeah->reno_count);

					tp->snd_ssthresh = tp->snd_cwnd;
				}

				if (yeah->reno_count <= 2)
					yeah->reno_count = max(tp->snd_cwnd>>1, 2U);
				else
					yeah->reno_count++;

				yeah->doing_reno_now = min(yeah->doing_reno_now + 1,
							   0xffffffU);
			} else {
				yeah->fast_count++;

				if (yeah->fast_count > TCP_YEAH_ZETA) {
					yeah->reno_count = 2;
					yeah->fast_count = 0;
				}

				yeah->doing_reno_now = 0;
			}

			yeah->lastQ = queue;

		}

		/* Save the extent of the current window so we can use this
		 * at the end of the next RTT.
		 */
		yeah->vegas.beg_snd_una  = yeah->vegas.beg_snd_nxt;
		yeah->vegas.beg_snd_nxt  = tp->snd_nxt;
		yeah->vegas.beg_snd_cwnd = tp->snd_cwnd;

		/* Wipe the slate clean for the next RTT. */
		yeah->vegas.cntRTT = 0;
		yeah->vegas.minRTT = 0x7fffffff;
	}
}