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
struct TYPE_2__ {scalar_t__ sack_ok; } ;
struct tcp_sock {TYPE_1__ rx_opt; int /*<<< orphan*/  out_of_order_queue; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_OFOPRUNED ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_mem_reclaim (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_sack_reset (TYPE_1__*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static int tcp_prune_ofo_queue(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	int res = 0;

	if (!skb_queue_empty(&tp->out_of_order_queue)) {
		NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_OFOPRUNED);
		__skb_queue_purge(&tp->out_of_order_queue);

		/* Reset SACK state.  A conforming SACK implementation will
		 * do the same at a timeout based retransmit.  When a connection
		 * is in a sad state like this, we care only about integrity
		 * of the connection not performance.
		 */
		if (tp->rx_opt.sack_ok)
			tcp_sack_reset(&tp->rx_opt);
		sk_mem_reclaim(sk);
		res = 1;
	}
	return res;
}