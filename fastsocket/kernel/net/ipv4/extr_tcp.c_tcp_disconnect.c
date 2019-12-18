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
struct tcp_sock {int snd_nxt; int write_seq; scalar_t__ max_window; int snd_cwnd; int /*<<< orphan*/  rx_opt; scalar_t__ bytes_acked; scalar_t__ snd_cwnd_cnt; int /*<<< orphan*/  snd_ssthresh; scalar_t__ packets_out; scalar_t__ srtt; int /*<<< orphan*/  out_of_order_queue; } ;
struct sock {int sk_state; int sk_userlocks; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;scalar_t__ sk_shutdown; int /*<<< orphan*/  sk_async_wait_queue; int /*<<< orphan*/  sk_receive_queue; void* sk_err; } ;
struct inet_sock {scalar_t__ num; scalar_t__ dport; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_bind_hash; scalar_t__ icsk_probes_out; scalar_t__ icsk_backoff; } ;

/* Variables and functions */
 void* ECONNRESET ; 
 int SOCK_BINDADDR_LOCK ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int TCPF_CLOSING ; 
 int TCPF_LAST_ACK ; 
 int /*<<< orphan*/  TCP_CA_Open ; 
 int TCP_CLOSE ; 
 int /*<<< orphan*/  TCP_INFINITE_SSTHRESH ; 
 int TCP_LISTEN ; 
 int TCP_SYN_SENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __sk_dst_reset (struct sock*) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfp_any () ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_delack_init (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_listen_stop (struct sock*) ; 
 int /*<<< orphan*/  inet_reset_saddr (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tcp_clear_retrans (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_clear_xmit_timers (struct sock*) ; 
 int /*<<< orphan*/  tcp_init_send_head (struct sock*) ; 
 scalar_t__ tcp_need_reset (int) ; 
 int /*<<< orphan*/  tcp_send_active_reset (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_set_ca_state (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_set_state (struct sock*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_write_queue_purge (struct sock*) ; 

int tcp_disconnect(struct sock *sk, int flags)
{
	struct inet_sock *inet = inet_sk(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	int err = 0;
	int old_state = sk->sk_state;

	if (old_state != TCP_CLOSE)
		tcp_set_state(sk, TCP_CLOSE);

	/* ABORT function of RFC793 */
	if (old_state == TCP_LISTEN) {
		inet_csk_listen_stop(sk);
	} else if (tcp_need_reset(old_state) ||
		   (tp->snd_nxt != tp->write_seq &&
		    (1 << old_state) & (TCPF_CLOSING | TCPF_LAST_ACK))) {
		/* The last check adjusts for discrepancy of Linux wrt. RFC
		 * states
		 */
		tcp_send_active_reset(sk, gfp_any());
		sk->sk_err = ECONNRESET;
	} else if (old_state == TCP_SYN_SENT)
		sk->sk_err = ECONNRESET;

	tcp_clear_xmit_timers(sk);
	__skb_queue_purge(&sk->sk_receive_queue);
	tcp_write_queue_purge(sk);
	__skb_queue_purge(&tp->out_of_order_queue);
#ifdef CONFIG_NET_DMA
	__skb_queue_purge(&sk->sk_async_wait_queue);
#endif

	inet->dport = 0;

	if (!(sk->sk_userlocks & SOCK_BINDADDR_LOCK))
		inet_reset_saddr(sk);

	sk->sk_shutdown = 0;
	sock_reset_flag(sk, SOCK_DONE);
	tp->srtt = 0;
	if ((tp->write_seq += tp->max_window + 2) == 0)
		tp->write_seq = 1;
	icsk->icsk_backoff = 0;
	tp->snd_cwnd = 2;
	icsk->icsk_probes_out = 0;
	tp->packets_out = 0;
	tp->snd_ssthresh = TCP_INFINITE_SSTHRESH;
	tp->snd_cwnd_cnt = 0;
	tp->bytes_acked = 0;
	tcp_set_ca_state(sk, TCP_CA_Open);
	tcp_clear_retrans(tp);
	inet_csk_delack_init(sk);
	tcp_init_send_head(sk);
	memset(&tp->rx_opt, 0, sizeof(tp->rx_opt));
	__sk_dst_reset(sk);

	WARN_ON(inet->num && !icsk->icsk_bind_hash);

	sk->sk_error_report(sk);
	return err;
}