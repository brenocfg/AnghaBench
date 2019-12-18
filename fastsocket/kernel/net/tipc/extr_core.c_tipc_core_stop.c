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
 scalar_t__ TIPC_NODE_MODE ; 
 scalar_t__ TIPC_NOT_RUNNING ; 
 int /*<<< orphan*/  tipc_cfg_stop () ; 
 int /*<<< orphan*/  tipc_handler_stop () ; 
 scalar_t__ tipc_mode ; 
 int /*<<< orphan*/  tipc_nametbl_stop () ; 
 int /*<<< orphan*/  tipc_netlink_stop () ; 
 int /*<<< orphan*/  tipc_ref_table_stop () ; 
 int /*<<< orphan*/  tipc_reg_stop () ; 
 int /*<<< orphan*/  tipc_socket_stop () ; 
 int /*<<< orphan*/  tipc_subscr_stop () ; 

void tipc_core_stop(void)
{
	if (tipc_mode != TIPC_NODE_MODE)
		return;

	tipc_mode = TIPC_NOT_RUNNING;

	tipc_netlink_stop();
	tipc_handler_stop();
	tipc_cfg_stop();
	tipc_subscr_stop();
	tipc_reg_stop();
	tipc_nametbl_stop();
	tipc_ref_table_stop();
	tipc_socket_stop();
}