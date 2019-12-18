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
typedef  scalar_t__ u32 ;
struct tcp_sock {scalar_t__ linger2; scalar_t__ packets_out; } ;
struct sock {scalar_t__ sk_state; } ;
struct inet_connection_sock {scalar_t__ icsk_probes_out; } ;
struct TYPE_2__ {scalar_t__ icsk_user_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  SOCK_KEEPOPEN ; 
 int /*<<< orphan*/  TCP_CHECK_TIMER (struct sock*) ; 
 scalar_t__ TCP_CLOSE ; 
 scalar_t__ TCP_FIN_WAIT2 ; 
 scalar_t__ TCP_LISTEN ; 
 scalar_t__ TCP_RESOURCE_PROBE_INTERVAL ; 
 int TCP_TIMEWAIT_LEN ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_keepalive_timer (struct sock*,scalar_t__) ; 
 scalar_t__ keepalive_intvl_when (struct tcp_sock*) ; 
 scalar_t__ keepalive_probes (struct tcp_sock*) ; 
 scalar_t__ keepalive_time_elapsed (struct tcp_sock*) ; 
 scalar_t__ keepalive_time_when (struct tcp_sock*) ; 
 TYPE_1__* sk_extended (struct sock*) ; 
 int /*<<< orphan*/  sk_mem_reclaim (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  tcp_done (struct sock*) ; 
 int tcp_fin_time (struct sock*) ; 
 int /*<<< orphan*/  tcp_send_active_reset (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_send_head (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_synack_timer (struct sock*) ; 
 int /*<<< orphan*/  tcp_time_wait (struct sock*,scalar_t__,int const) ; 
 int /*<<< orphan*/  tcp_write_err (struct sock*) ; 
 scalar_t__ tcp_write_wakeup (struct sock*) ; 

__attribute__((used)) static void tcp_keepalive_timer (unsigned long data)
{
	struct sock *sk = (struct sock *) data;
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	u32 elapsed;

	/* Only process if socket is not in use. */
	bh_lock_sock(sk);
	if (sock_owned_by_user(sk)) {
		/* Try again later. */
		inet_csk_reset_keepalive_timer (sk, HZ/20);
		goto out;
	}

	if (sk->sk_state == TCP_LISTEN) {
		tcp_synack_timer(sk);
		goto out;
	}

	if (sk->sk_state == TCP_FIN_WAIT2 && sock_flag(sk, SOCK_DEAD)) {
		if (tp->linger2 >= 0) {
			const int tmo = tcp_fin_time(sk) - TCP_TIMEWAIT_LEN;

			if (tmo > 0) {
				tcp_time_wait(sk, TCP_FIN_WAIT2, tmo);
				goto out;
			}
		}
		tcp_send_active_reset(sk, GFP_ATOMIC);
		goto death;
	}

	if (!sock_flag(sk, SOCK_KEEPOPEN) || sk->sk_state == TCP_CLOSE)
		goto out;

	elapsed = keepalive_time_when(tp);

	/* It is alive without keepalive 8) */
	if (tp->packets_out || tcp_send_head(sk))
		goto resched;

	elapsed = keepalive_time_elapsed(tp);

	if (elapsed >= keepalive_time_when(tp)) {
		u32 icsk_user_timeout = sk_extended(sk)->icsk_user_timeout;

		/* If the TCP_USER_TIMEOUT option is enabled, use that
		 * to determine when to timeout instead.
		 */
		if ((icsk_user_timeout != 0 &&
		    elapsed >= icsk_user_timeout &&
		    icsk->icsk_probes_out > 0) ||
		    (icsk_user_timeout == 0 &&
		    icsk->icsk_probes_out >= keepalive_probes(tp))) {
			tcp_send_active_reset(sk, GFP_ATOMIC);
			tcp_write_err(sk);
			goto out;
		}
		if (tcp_write_wakeup(sk) <= 0) {
			icsk->icsk_probes_out++;
			elapsed = keepalive_intvl_when(tp);
		} else {
			/* If keepalive was lost due to local congestion,
			 * try harder.
			 */
			elapsed = TCP_RESOURCE_PROBE_INTERVAL;
		}
	} else {
		/* It is tp->rcv_tstamp + keepalive_time_when(tp) */
		elapsed = keepalive_time_when(tp) - elapsed;
	}

	TCP_CHECK_TIMER(sk);
	sk_mem_reclaim(sk);

resched:
	inet_csk_reset_keepalive_timer (sk, elapsed);
	goto out;

death:
	tcp_done(sk);

out:
	bh_unlock_sock(sk);
	sock_put(sk);
}