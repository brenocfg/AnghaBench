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
struct sock {int sk_state; int sk_userlocks; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;scalar_t__ sk_shutdown; int /*<<< orphan*/ * sk_send_head; int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_receive_queue; void* sk_err; } ;
struct inet_sock {scalar_t__ num; scalar_t__ dport; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_bind_hash; scalar_t__ icsk_backoff; } ;

/* Variables and functions */
 int const DCCP_CLOSED ; 
 int const DCCP_LISTEN ; 
 int const DCCP_REQUESTING ; 
 int /*<<< orphan*/  DCCP_RESET_CODE_ABORTED ; 
 void* ECONNRESET ; 
 int SOCK_BINDADDR_LOCK ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __sk_dst_reset (struct sock*) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dccp_clear_xmit_timers (struct sock*) ; 
 scalar_t__ dccp_need_reset (int const) ; 
 int /*<<< orphan*/  dccp_send_reset (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_set_state (struct sock*,int const) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_delack_init (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_listen_stop (struct sock*) ; 
 int /*<<< orphan*/  inet_reset_saddr (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

int dccp_disconnect(struct sock *sk, int flags)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct inet_sock *inet = inet_sk(sk);
	int err = 0;
	const int old_state = sk->sk_state;

	if (old_state != DCCP_CLOSED)
		dccp_set_state(sk, DCCP_CLOSED);

	/*
	 * This corresponds to the ABORT function of RFC793, sec. 3.8
	 * TCP uses a RST segment, DCCP a Reset packet with Code 2, "Aborted".
	 */
	if (old_state == DCCP_LISTEN) {
		inet_csk_listen_stop(sk);
	} else if (dccp_need_reset(old_state)) {
		dccp_send_reset(sk, DCCP_RESET_CODE_ABORTED);
		sk->sk_err = ECONNRESET;
	} else if (old_state == DCCP_REQUESTING)
		sk->sk_err = ECONNRESET;

	dccp_clear_xmit_timers(sk);

	__skb_queue_purge(&sk->sk_receive_queue);
	__skb_queue_purge(&sk->sk_write_queue);
	if (sk->sk_send_head != NULL) {
		__kfree_skb(sk->sk_send_head);
		sk->sk_send_head = NULL;
	}

	inet->dport = 0;

	if (!(sk->sk_userlocks & SOCK_BINDADDR_LOCK))
		inet_reset_saddr(sk);

	sk->sk_shutdown = 0;
	sock_reset_flag(sk, SOCK_DONE);

	icsk->icsk_backoff = 0;
	inet_csk_delack_init(sk);
	__sk_dst_reset(sk);

	WARN_ON(inet->num && !icsk->icsk_bind_hash);

	sk->sk_error_report(sk);
	return err;
}