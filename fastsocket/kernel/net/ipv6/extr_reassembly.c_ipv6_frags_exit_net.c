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
struct TYPE_2__ {int /*<<< orphan*/  frags; } ;
struct net {TYPE_1__ ipv6; } ;

/* Variables and functions */
 int /*<<< orphan*/  inet_frags_exit_net (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_frags ; 
 int /*<<< orphan*/  ip6_frags_ns_sysctl_unregister (struct net*) ; 

__attribute__((used)) static void ipv6_frags_exit_net(struct net *net)
{
	ip6_frags_ns_sysctl_unregister(net);
	inet_frags_exit_net(&net->ipv6.frags, &ip6_frags);
}