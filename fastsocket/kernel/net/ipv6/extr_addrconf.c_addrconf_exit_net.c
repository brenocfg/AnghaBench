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
struct TYPE_2__ {int /*<<< orphan*/  devconf_all; int /*<<< orphan*/  devconf_dflt; } ;
struct net {TYPE_1__ ipv6; } ;

/* Variables and functions */
 int /*<<< orphan*/  __addrconf_sysctl_unregister (int /*<<< orphan*/ ) ; 
 struct net init_net ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void addrconf_exit_net(struct net *net)
{
#ifdef CONFIG_SYSCTL
	__addrconf_sysctl_unregister(net->ipv6.devconf_dflt);
	__addrconf_sysctl_unregister(net->ipv6.devconf_all);
#endif
	if (net != &init_net) {
		kfree(net->ipv6.devconf_dflt);
		kfree(net->ipv6.devconf_all);
	}
}