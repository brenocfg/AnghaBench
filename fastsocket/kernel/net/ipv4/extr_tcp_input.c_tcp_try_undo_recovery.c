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
struct tcp_sock {scalar_t__ snd_una; scalar_t__ high_seq; scalar_t__ undo_marker; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ icsk_ca_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGUNDO (struct sock*,char*) ; 
 int LINUX_MIB_TCPFULLUNDO ; 
 int LINUX_MIB_TCPLOSSUNDO ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TCP_CA_Loss ; 
 int /*<<< orphan*/  TCP_CA_Open ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ tcp_is_reno (struct tcp_sock*) ; 
 scalar_t__ tcp_may_undo (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_moderate_cwnd (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_set_ca_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_undo_cwr (struct sock*,int) ; 

__attribute__((used)) static int tcp_try_undo_recovery(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (tcp_may_undo(tp)) {
		int mib_idx;

		/* Happy end! We did not retransmit anything
		 * or our original transmission succeeded.
		 */
		DBGUNDO(sk, inet_csk(sk)->icsk_ca_state == TCP_CA_Loss ? "loss" : "retrans");
		tcp_undo_cwr(sk, true);
		if (inet_csk(sk)->icsk_ca_state == TCP_CA_Loss)
			mib_idx = LINUX_MIB_TCPLOSSUNDO;
		else
			mib_idx = LINUX_MIB_TCPFULLUNDO;

		NET_INC_STATS_BH(sock_net(sk), mib_idx);
		tp->undo_marker = 0;
	}
	if (tp->snd_una == tp->high_seq && tcp_is_reno(tp)) {
		/* Hold old state until something *above* high_seq
		 * is ACKed. For Reno it is MUST to prevent false
		 * fast retransmits (RFC2582). SACK TCP is safe. */
		tcp_moderate_cwnd(tp);
		return 1;
	}
	tcp_set_ca_state(sk, TCP_CA_Open);
	return 0;
}