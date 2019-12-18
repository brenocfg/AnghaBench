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
struct tcp_sock {scalar_t__ packets_out; } ;
struct sock {int dummy; } ;
struct inet_connection_sock {int icsk_probes_out; int icsk_rto; int icsk_backoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DEAD ; 
 int TCP_RTO_MAX ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int sysctl_tcp_retries2 ; 
 int tcp_orphan_retries (struct sock*,int const) ; 
 scalar_t__ tcp_out_of_resources (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_send_head (struct sock*) ; 
 int /*<<< orphan*/  tcp_send_probe0 (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_write_err (struct sock*) ; 

__attribute__((used)) static void tcp_probe_timer(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	int max_probes;

	if (tp->packets_out || !tcp_send_head(sk)) {
		icsk->icsk_probes_out = 0;
		return;
	}

	/* *WARNING* RFC 1122 forbids this
	 *
	 * It doesn't AFAIK, because we kill the retransmit timer -AK
	 *
	 * FIXME: We ought not to do it, Solaris 2.5 actually has fixing
	 * this behaviour in Solaris down as a bug fix. [AC]
	 *
	 * Let me to explain. icsk_probes_out is zeroed by incoming ACKs
	 * even if they advertise zero window. Hence, connection is killed only
	 * if we received no ACKs for normal connection timeout. It is not killed
	 * only because window stays zero for some time, window may be zero
	 * until armageddon and even later. We are in full accordance
	 * with RFCs, only probe timer combines both retransmission timeout
	 * and probe timeout in one bottle.				--ANK
	 */
	max_probes = sysctl_tcp_retries2;

	if (sock_flag(sk, SOCK_DEAD)) {
		const int alive = ((icsk->icsk_rto << icsk->icsk_backoff) < TCP_RTO_MAX);

		max_probes = tcp_orphan_retries(sk, alive);

		if (tcp_out_of_resources(sk, alive || icsk->icsk_probes_out <= max_probes))
			return;
	}

	if (icsk->icsk_probes_out > max_probes) {
		tcp_write_err(sk);
	} else {
		/* Only send another probe if we didn't close things up. */
		tcp_send_probe0(sk);
	}
}