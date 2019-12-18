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
struct tcp_sock {scalar_t__ reordering; scalar_t__ retrans_out; scalar_t__ retrans_stamp; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGUNDO (struct sock*,char*) ; 
 int /*<<< orphan*/  LINUX_MIB_TCPPARTIALUNDO ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ tcp_fackets_out (struct tcp_sock*) ; 
 scalar_t__ tcp_is_reno (struct tcp_sock*) ; 
 scalar_t__ tcp_may_undo (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_undo_cwr (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_update_reordering (struct sock*,scalar_t__,int) ; 

__attribute__((used)) static int tcp_try_undo_partial(struct sock *sk, int acked)
{
	struct tcp_sock *tp = tcp_sk(sk);
	/* Partial ACK arrived. Force Hoe's retransmit. */
	int failed = tcp_is_reno(tp) || (tcp_fackets_out(tp) > tp->reordering);

	if (tcp_may_undo(tp)) {
		/* Plain luck! Hole if filled with delayed
		 * packet, rather than with a retransmit.
		 */
		if (tp->retrans_out == 0)
			tp->retrans_stamp = 0;

		tcp_update_reordering(sk, tcp_fackets_out(tp) + acked, 1);

		DBGUNDO(sk, "Hoe");
		tcp_undo_cwr(sk, false);
		NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPPARTIALUNDO);

		/* So... Do not make Hoe's retransmit yet.
		 * If the first packet was delayed, the rest
		 * ones are most probably delayed as well.
		 */
		failed = 0;
	}
	return failed;
}