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
 int /*<<< orphan*/  genl_unregister_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_genl_family ; 
 scalar_t__ tipc_genl_family_registered ; 

void tipc_netlink_stop(void)
{
	if (!tipc_genl_family_registered)
		return;

	genl_unregister_family(&tipc_genl_family);
	tipc_genl_family_registered = 0;
}