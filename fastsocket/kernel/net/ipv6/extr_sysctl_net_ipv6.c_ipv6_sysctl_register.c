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
 int ENOMEM ; 
 int /*<<< orphan*/ * ip6_header ; 
 int /*<<< orphan*/  ipv6_rotable ; 
 int /*<<< orphan*/  ipv6_sysctl_net_ops ; 
 int /*<<< orphan*/  net_ipv6_ctl_path ; 
 int /*<<< orphan*/ * register_net_sysctl_rotable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_pernet_subsys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_net_sysctl_table (int /*<<< orphan*/ *) ; 

int ipv6_sysctl_register(void)
{
	int err = -ENOMEM;

	ip6_header = register_net_sysctl_rotable(net_ipv6_ctl_path, ipv6_rotable);
	if (ip6_header == NULL)
		goto out;

	err = register_pernet_subsys(&ipv6_sysctl_net_ops);
	if (err)
		goto err_pernet;
out:
	return err;

err_pernet:
	unregister_net_sysctl_table(ip6_header);
	goto out;
}