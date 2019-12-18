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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {struct dcbnl_rtnl_ops* dcbnl_ops; } ;
struct net {int dummy; } ;
struct dcbnl_rtnl_ops {int dummy; } ;
struct dcbmsg {int /*<<< orphan*/  cmd; int /*<<< orphan*/  dcb_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  DCB_CMD_IEEE_GET ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dcbmsg* NLMSG_DATA (struct nlmsghdr*) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  RTM_GETDCB ; 
 int dcbnl_ieee_fill (struct sk_buff*,struct net_device*) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcbnl_ieee_get(struct net_device *netdev, struct nlattr **tb,
			  u32 pid, u32 seq, u16 flags)
{
	struct net *net = dev_net(netdev);
	struct sk_buff *skb;
	struct nlmsghdr *nlh;
	struct dcbmsg *dcb;
	const struct dcbnl_rtnl_ops *ops = netdev->dcbnl_ops;
	int err;

	if (!ops)
		return -EOPNOTSUPP;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!skb)
		return -ENOBUFS;

	nlh = nlmsg_put(skb, pid, seq, RTM_GETDCB, sizeof(*dcb), flags);
	if (nlh == NULL) {
		nlmsg_free(skb);
		return -EMSGSIZE;
	}

	dcb = NLMSG_DATA(nlh);
	dcb->dcb_family = AF_UNSPEC;
	dcb->cmd = DCB_CMD_IEEE_GET;

	err = dcbnl_ieee_fill(skb, netdev);

	if (err < 0) {
		nlmsg_cancel(skb, nlh);
		kfree_skb(skb);
	} else {
		nlmsg_end(skb, nlh);
		err = rtnl_unicast(skb, net, pid);
	}

	return err;
}