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
typedef  int u32 ;
struct tcp_sock {scalar_t__ snd_cwnd; scalar_t__ snd_ssthresh; int snd_cwnd_cnt; scalar_t__ snd_cwnd_clamp; } ;
struct sock {int dummy; } ;
struct illinois {int acked; int alpha; int /*<<< orphan*/  end_seq; } ;

/* Variables and functions */
 int ALPHA_SHIFT ; 
 scalar_t__ after (int,int /*<<< orphan*/ ) ; 
 struct illinois* inet_csk_ca (struct sock*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  tcp_is_cwnd_limited (struct sock*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_slow_start (struct tcp_sock*) ; 
 int /*<<< orphan*/  update_params (struct sock*) ; 

__attribute__((used)) static void tcp_illinois_cong_avoid(struct sock *sk, u32 ack, u32 in_flight)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct illinois *ca = inet_csk_ca(sk);

	if (after(ack, ca->end_seq))
		update_params(sk);

	/* RFC2861 only increase cwnd if fully utilized */
	if (!tcp_is_cwnd_limited(sk, in_flight))
		return;

	/* In slow start */
	if (tp->snd_cwnd <= tp->snd_ssthresh)
		tcp_slow_start(tp);

	else {
		u32 delta;

		/* snd_cwnd_cnt is # of packets since last cwnd increment */
		tp->snd_cwnd_cnt += ca->acked;
		ca->acked = 1;

		/* This is close approximation of:
		 * tp->snd_cwnd += alpha/tp->snd_cwnd
		*/
		delta = (tp->snd_cwnd_cnt * ca->alpha) >> ALPHA_SHIFT;
		if (delta >= tp->snd_cwnd) {
			tp->snd_cwnd = min(tp->snd_cwnd + delta / tp->snd_cwnd,
					   (u32) tp->snd_cwnd_clamp);
			tp->snd_cwnd_cnt = 0;
		}
	}
}