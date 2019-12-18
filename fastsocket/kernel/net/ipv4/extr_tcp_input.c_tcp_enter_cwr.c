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
struct tcp_sock {int /*<<< orphan*/  snd_cwnd_stamp; int /*<<< orphan*/  snd_nxt; int /*<<< orphan*/  high_seq; scalar_t__ snd_cwnd_cnt; int /*<<< orphan*/  snd_cwnd; int /*<<< orphan*/  snd_ssthresh; scalar_t__ undo_marker; scalar_t__ bytes_acked; scalar_t__ prior_ssthresh; } ;
struct sock {int dummy; } ;
struct inet_connection_sock {scalar_t__ icsk_ca_state; TYPE_1__* icsk_ca_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ssthresh ) (struct sock*) ;} ;

/* Variables and functions */
 scalar_t__ TCP_CA_CWR ; 
 int /*<<< orphan*/  TCP_ECN_queue_cwr (struct tcp_sock*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 scalar_t__ tcp_packets_in_flight (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_set_ca_state (struct sock*,scalar_t__) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_time_stamp ; 

void tcp_enter_cwr(struct sock *sk, const int set_ssthresh)
{
	struct tcp_sock *tp = tcp_sk(sk);
	const struct inet_connection_sock *icsk = inet_csk(sk);

	tp->prior_ssthresh = 0;
	tp->bytes_acked = 0;
	if (icsk->icsk_ca_state < TCP_CA_CWR) {
		tp->undo_marker = 0;
		if (set_ssthresh)
			tp->snd_ssthresh = icsk->icsk_ca_ops->ssthresh(sk);
		tp->snd_cwnd = min(tp->snd_cwnd,
				   tcp_packets_in_flight(tp) + 1U);
		tp->snd_cwnd_cnt = 0;
		tp->high_seq = tp->snd_nxt;
		tp->snd_cwnd_stamp = tcp_time_stamp;
		TCP_ECN_queue_cwr(tp);

		tcp_set_ca_state(sk, TCP_CA_CWR);
	}
}