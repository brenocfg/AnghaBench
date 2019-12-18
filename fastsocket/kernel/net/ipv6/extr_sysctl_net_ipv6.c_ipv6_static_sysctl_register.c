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
struct ctl_table {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * ip6_base ; 
 int /*<<< orphan*/  net_ipv6_ctl_path ; 
 int /*<<< orphan*/ * register_sysctl_paths (int /*<<< orphan*/ ,struct ctl_table*) ; 

int ipv6_static_sysctl_register(void)
{
	static struct ctl_table empty[1];
	ip6_base = register_sysctl_paths(net_ipv6_ctl_path, empty);
	if (ip6_base == NULL)
		return -ENOMEM;
	return 0;
}