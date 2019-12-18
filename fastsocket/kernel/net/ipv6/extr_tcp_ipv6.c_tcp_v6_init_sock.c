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
struct tcp_sock {int snd_cwnd; int mss_cache; int /*<<< orphan*/ * af_specific; int /*<<< orphan*/  reordering; int /*<<< orphan*/  snd_cwnd_clamp; int /*<<< orphan*/  snd_ssthresh; void* mdev; int /*<<< orphan*/  tsq_node; int /*<<< orphan*/  out_of_order_queue; } ;
struct sock {int /*<<< orphan*/  sk_rcvbuf; int /*<<< orphan*/  sk_sndbuf; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_state; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_sync_mss; int /*<<< orphan*/ * icsk_ca_ops; int /*<<< orphan*/ * icsk_af_ops; void* icsk_rto; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_USE_WRITE_QUEUE ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  TCP_INFINITE_SSTHRESH ; 
 void* TCP_TIMEOUT_INIT ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  ipv6_specific ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_stream_write_space ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_tcp_reordering ; 
 int /*<<< orphan*/ * sysctl_tcp_rmem ; 
 int /*<<< orphan*/ * sysctl_tcp_wmem ; 
 int /*<<< orphan*/  tcp_init_congestion_ops ; 
 int /*<<< orphan*/  tcp_init_xmit_timers (struct sock*) ; 
 int /*<<< orphan*/  tcp_prequeue_init (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_sock_ipv6_specific ; 
 int /*<<< orphan*/  tcp_sockets_allocated ; 
 int /*<<< orphan*/  tcp_sync_mss ; 

__attribute__((used)) static int tcp_v6_init_sock(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);

	skb_queue_head_init(&tp->out_of_order_queue);
	tcp_init_xmit_timers(sk);
	tcp_prequeue_init(tp);
	INIT_LIST_HEAD(&tp->tsq_node);

	icsk->icsk_rto = TCP_TIMEOUT_INIT;
	tp->mdev = TCP_TIMEOUT_INIT;

	/* So many TCP implementations out there (incorrectly) count the
	 * initial SYN frame in their delayed-ACK and congestion control
	 * algorithms that we must have the following bandaid to talk
	 * efficiently to them.  -DaveM
	 */
	tp->snd_cwnd = 2;

	/* See draft-stevens-tcpca-spec-01 for discussion of the
	 * initialization of these values.
	 */
	tp->snd_ssthresh = TCP_INFINITE_SSTHRESH;
	tp->snd_cwnd_clamp = ~0;
	tp->mss_cache = 536;

	tp->reordering = sysctl_tcp_reordering;

	sk->sk_state = TCP_CLOSE;

	icsk->icsk_af_ops = &ipv6_specific;
	icsk->icsk_ca_ops = &tcp_init_congestion_ops;
	icsk->icsk_sync_mss = tcp_sync_mss;
	sk->sk_write_space = sk_stream_write_space;
	sock_set_flag(sk, SOCK_USE_WRITE_QUEUE);

#ifdef CONFIG_TCP_MD5SIG
	tp->af_specific = &tcp_sock_ipv6_specific;
#endif

	sk->sk_sndbuf = sysctl_tcp_wmem[1];
	sk->sk_rcvbuf = sysctl_tcp_rmem[1];

	local_bh_disable();
	percpu_counter_inc(&tcp_sockets_allocated);
	local_bh_enable();

	return 0;
}