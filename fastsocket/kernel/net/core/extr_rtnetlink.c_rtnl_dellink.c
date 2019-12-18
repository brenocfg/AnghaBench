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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct rtnl_link_ops {int /*<<< orphan*/  (* dellink ) (struct net_device*) ;} ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {struct rtnl_link_ops* rtnl_link_ops; } ;
struct net {int dummy; } ;
struct ifinfomsg {scalar_t__ ifi_index; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 size_t IFLA_IFNAME ; 
 int /*<<< orphan*/  IFLA_MAX ; 
 int IFNAMSIZ ; 
 struct net_device* __dev_get_by_index (struct net*,scalar_t__) ; 
 struct net_device* __dev_get_by_name (struct net*,char*) ; 
 int /*<<< orphan*/  ifla_policy ; 
 int /*<<< orphan*/  nla_strlcpy (char*,struct nlattr*,int) ; 
 struct ifinfomsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

__attribute__((used)) static int rtnl_dellink(struct sk_buff *skb, struct nlmsghdr *nlh, void *arg)
{
	struct net *net = sock_net(skb->sk);
	const struct rtnl_link_ops *ops;
	struct net_device *dev;
	struct ifinfomsg *ifm;
	char ifname[IFNAMSIZ];
	struct nlattr *tb[IFLA_MAX+1];
	int err;

	err = nlmsg_parse(nlh, sizeof(*ifm), tb, IFLA_MAX, ifla_policy);
	if (err < 0)
		return err;

	if (tb[IFLA_IFNAME])
		nla_strlcpy(ifname, tb[IFLA_IFNAME], IFNAMSIZ);

	ifm = nlmsg_data(nlh);
	if (ifm->ifi_index > 0)
		dev = __dev_get_by_index(net, ifm->ifi_index);
	else if (tb[IFLA_IFNAME])
		dev = __dev_get_by_name(net, ifname);
	else
		return -EINVAL;

	if (!dev)
		return -ENODEV;

	ops = dev->rtnl_link_ops;
	if (!ops)
		return -EOPNOTSUPP;

	ops->dellink(dev);
	return 0;
}