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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ifinfomsg {scalar_t__ ifi_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFLA_MAX ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct net_device* dev_get_by_index (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  get_ext_mask (struct nlattr**) ; 
 int /*<<< orphan*/  if_nlmsg_size (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifla_policy ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct ifinfomsg* nlmsg_data (struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtnl_fill_ifinfo (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtnl_getlink(struct sk_buff *skb, struct nlmsghdr* nlh, void *arg)
{
	struct net *net = sock_net(skb->sk);
	struct ifinfomsg *ifm;
	struct nlattr *tb[IFLA_MAX+1];
	struct net_device *dev = NULL;
	struct sk_buff *nskb;
	int err;
	u32 ext_filter_mask = 0;

	err = nlmsg_parse(nlh, sizeof(*ifm), tb, IFLA_MAX, ifla_policy);
	if (err < 0)
		return err;

	ext_filter_mask = get_ext_mask(tb);

	ifm = nlmsg_data(nlh);
	if (ifm->ifi_index > 0) {
		dev = dev_get_by_index(net, ifm->ifi_index);
		if (dev == NULL)
			return -ENODEV;
	} else
		return -EINVAL;

	nskb = nlmsg_new(if_nlmsg_size(dev, ext_filter_mask), GFP_KERNEL);
	if (nskb == NULL) {
		err = -ENOBUFS;
		goto errout;
	}

	err = rtnl_fill_ifinfo(nskb, dev, RTM_NEWLINK, NETLINK_CB(skb).pid,
			       nlh->nlmsg_seq, 0, 0, ext_filter_mask);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in if_nlmsg_size */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(nskb);
		goto errout;
	}
	err = rtnl_unicast(nskb, net, NETLINK_CB(skb).pid);
errout:
	dev_put(dev);

	return err;
}