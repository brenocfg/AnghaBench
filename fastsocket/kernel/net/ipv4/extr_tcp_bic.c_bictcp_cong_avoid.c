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
typedef  int /*<<< orphan*/  u32 ;
struct tcp_sock {scalar_t__ snd_cwnd; scalar_t__ snd_ssthresh; } ;
struct sock {int dummy; } ;
struct bictcp {int /*<<< orphan*/  cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  bictcp_update (struct bictcp*,scalar_t__) ; 
 struct bictcp* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  tcp_cong_avoid_ai (struct tcp_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_is_cwnd_limited (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_slow_start (struct tcp_sock*) ; 

__attribute__((used)) static void bictcp_cong_avoid(struct sock *sk, u32 ack, u32 in_flight)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct bictcp *ca = inet_csk_ca(sk);

	if (!tcp_is_cwnd_limited(sk, in_flight))
		return;

	if (tp->snd_cwnd <= tp->snd_ssthresh)
		tcp_slow_start(tp);
	else {
		bictcp_update(ca, tp->snd_cwnd);
		tcp_cong_avoid_ai(tp, ca->cnt);
	}

}