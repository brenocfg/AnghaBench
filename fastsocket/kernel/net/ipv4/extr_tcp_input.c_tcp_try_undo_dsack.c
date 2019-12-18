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
struct tcp_sock {scalar_t__ undo_marker; int /*<<< orphan*/  undo_retrans; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGUNDO (struct sock*,char*) ; 
 int /*<<< orphan*/  LINUX_MIB_TCPDSACKUNDO ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_undo_cwr (struct sock*,int) ; 

__attribute__((used)) static void tcp_try_undo_dsack(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (tp->undo_marker && !tp->undo_retrans) {
		DBGUNDO(sk, "D-SACK");
		tcp_undo_cwr(sk, true);
		tp->undo_marker = 0;
		NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPDSACKUNDO);
	}
}