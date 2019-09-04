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
struct socket {int /*<<< orphan*/  so_traffic_class; int /*<<< orphan*/  so_flags1; } ;

/* Variables and functions */
 scalar_t__ IS_TCP_RECV_BG (struct socket*) ; 
 int /*<<< orphan*/  SOF1_TRAFFIC_MGT_TCP_RECVBG ; 
 int /*<<< orphan*/  so_set_lro (struct socket*,int /*<<< orphan*/ ) ; 

void
tcp_clear_recv_bg(struct socket *so)
{
	if (IS_TCP_RECV_BG(so))
		so->so_flags1 &= ~(SOF1_TRAFFIC_MGT_TCP_RECVBG);

	/*
	 * Set/unset use of Large Receive Offload depending on
	 * the traffic class
	 */
	so_set_lro(so, so->so_traffic_class);
}