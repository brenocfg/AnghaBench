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
struct tcp_sock {int snd_cwnd; void* rcv_ssthresh; int /*<<< orphan*/  snd_cwnd_stamp; scalar_t__ snd_cwnd_cnt; int /*<<< orphan*/  mss_cache; void* prior_ssthresh; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int probe_size; int search_low; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_pmtu_cookie; TYPE_1__ icsk_mtup; } ;

/* Variables and functions */
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 void* tcp_current_ssthresh (struct sock*) ; 
 int tcp_mss_to_mtu (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_sync_mss (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_time_stamp ; 

__attribute__((used)) static void tcp_mtup_probe_success(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);

	/* FIXME: breaks with very large cwnd */
	tp->prior_ssthresh = tcp_current_ssthresh(sk);
	tp->snd_cwnd = tp->snd_cwnd *
		       tcp_mss_to_mtu(sk, tp->mss_cache) /
		       icsk->icsk_mtup.probe_size;
	tp->snd_cwnd_cnt = 0;
	tp->snd_cwnd_stamp = tcp_time_stamp;
	tp->rcv_ssthresh = tcp_current_ssthresh(sk);

	icsk->icsk_mtup.search_low = icsk->icsk_mtup.probe_size;
	icsk->icsk_mtup.probe_size = 0;
	tcp_sync_mss(sk, icsk->icsk_pmtu_cookie);
}