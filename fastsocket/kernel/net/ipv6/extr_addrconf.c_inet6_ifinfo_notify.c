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
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct inet6_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RTNLGRP_IPV6_IFADDR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int inet6_fill_ifinfo (struct sk_buff*,struct inet6_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_if_nlmsg_size () ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (struct net*,int /*<<< orphan*/ ,int) ; 

void inet6_ifinfo_notify(int event, struct inet6_dev *idev)
{
	struct sk_buff *skb;
	struct net *net = dev_net(idev->dev);
	int err = -ENOBUFS;

	skb = nlmsg_new(inet6_if_nlmsg_size(), GFP_ATOMIC);
	if (skb == NULL)
		goto errout;

	err = inet6_fill_ifinfo(skb, idev, 0, 0, event, 0);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in inet6_if_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout;
	}
	rtnl_notify(skb, net, 0, RTNLGRP_IPV6_IFADDR, NULL, GFP_ATOMIC);
	return;
errout:
	if (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_IPV6_IFADDR, err);
}