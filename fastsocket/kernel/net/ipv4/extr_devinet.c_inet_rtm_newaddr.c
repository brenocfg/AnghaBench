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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct net {int dummy; } ;
struct in_ifaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 scalar_t__ IS_ERR (struct in_ifaddr*) ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int PTR_ERR (struct in_ifaddr*) ; 
 int __inet_insert_ifa (struct in_ifaddr*,struct nlmsghdr*,int /*<<< orphan*/ ) ; 
 struct in_ifaddr* rtm_to_ifaddr (struct net*,struct nlmsghdr*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet_rtm_newaddr(struct sk_buff *skb, struct nlmsghdr *nlh, void *arg)
{
	struct net *net = sock_net(skb->sk);
	struct in_ifaddr *ifa;

	ASSERT_RTNL();

	ifa = rtm_to_ifaddr(net, nlh);
	if (IS_ERR(ifa))
		return PTR_ERR(ifa);

	return __inet_insert_ifa(ifa, nlh, NETLINK_CB(skb).pid);
}