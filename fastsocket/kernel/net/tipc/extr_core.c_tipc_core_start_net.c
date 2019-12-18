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
 int /*<<< orphan*/  tipc_core_stop_net () ; 
 int tipc_eth_media_start () ; 
 int tipc_net_start (unsigned long) ; 

int tipc_core_start_net(unsigned long addr)
{
	int res;

	if ((res = tipc_net_start(addr)) ||
	    (res = tipc_eth_media_start())) {
		tipc_core_stop_net();
	}
	return res;
}