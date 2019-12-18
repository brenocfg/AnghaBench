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
struct sock {int dummy; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_rto; int /*<<< orphan*/  icsk_retransmits; } ;

/* Variables and functions */
 int FLAG_SACK_RENEGING ; 
 int /*<<< orphan*/  ICSK_TIME_RETRANS ; 
 int /*<<< orphan*/  LINUX_MIB_TCPSACKRENEGING ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_RTO_MAX ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_enter_loss (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_retransmit_skb (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_write_queue_head (struct sock*) ; 

__attribute__((used)) static int tcp_check_sack_reneging(struct sock *sk, int flag)
{
	if (flag & FLAG_SACK_RENEGING) {
		struct inet_connection_sock *icsk = inet_csk(sk);
		NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPSACKRENEGING);

		tcp_enter_loss(sk, 1);
		icsk->icsk_retransmits++;
		tcp_retransmit_skb(sk, tcp_write_queue_head(sk));
		inet_csk_reset_xmit_timer(sk, ICSK_TIME_RETRANS,
					  icsk->icsk_rto, TCP_RTO_MAX);
		return 1;
	}
	return 0;
}