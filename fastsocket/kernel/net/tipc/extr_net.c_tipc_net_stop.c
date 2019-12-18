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

/* Variables and functions */
 scalar_t__ TIPC_NET_MODE ; 
 scalar_t__ TIPC_NODE_MODE ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  net_stop () ; 
 int /*<<< orphan*/  tipc_bclink_stop () ; 
 int /*<<< orphan*/  tipc_bearer_stop () ; 
 scalar_t__ tipc_mode ; 
 int /*<<< orphan*/  tipc_net_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void tipc_net_stop(void)
{
	if (tipc_mode != TIPC_NET_MODE)
		return;
	write_lock_bh(&tipc_net_lock);
	tipc_bearer_stop();
	tipc_mode = TIPC_NODE_MODE;
	tipc_bclink_stop();
	net_stop();
	write_unlock_bh(&tipc_net_lock);
	info("Left network mode \n");
}