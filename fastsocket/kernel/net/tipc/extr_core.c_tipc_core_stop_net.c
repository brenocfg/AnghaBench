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
 int /*<<< orphan*/  tipc_eth_media_stop () ; 
 int /*<<< orphan*/  tipc_net_stop () ; 

void tipc_core_stop_net(void)
{
	tipc_eth_media_stop();
	tipc_net_stop();
}