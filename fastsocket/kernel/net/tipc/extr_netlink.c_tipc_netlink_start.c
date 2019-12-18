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
 int /*<<< orphan*/  err (char*) ; 
 int genl_register_family_with_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tipc_genl_family ; 
 int tipc_genl_family_registered ; 
 int /*<<< orphan*/  tipc_genl_ops ; 

int tipc_netlink_start(void)
{
	int res;

	res = genl_register_family_with_ops(&tipc_genl_family,
		&tipc_genl_ops, 1);
	if (res) {
		err("Failed to register netlink interface\n");
		return res;
	}

	tipc_genl_family_registered = 1;
	return 0;
}