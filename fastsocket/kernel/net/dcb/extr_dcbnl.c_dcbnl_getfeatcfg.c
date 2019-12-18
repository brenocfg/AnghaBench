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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {TYPE_1__* dcbnl_ops; } ;
struct dcbmsg {int /*<<< orphan*/  cmd; int /*<<< orphan*/  dcb_family; } ;
struct TYPE_2__ {int (* getfeatcfg ) (struct net_device*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 size_t DCB_ATTR_FEATCFG ; 
 int /*<<< orphan*/  DCB_CMD_GFEATCFG ; 
 size_t DCB_FEATCFG_ATTR_ALL ; 
 int DCB_FEATCFG_ATTR_MAX ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dcbmsg* NLMSG_DATA (struct nlmsghdr*) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 struct nlmsghdr* NLMSG_NEW (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTM_GETDCB ; 
 int /*<<< orphan*/  dcbnl_featcfg_nest ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,size_t) ; 
 int nla_parse_nested (struct nlattr**,int,struct nlattr*,int /*<<< orphan*/ ) ; 
 int nla_put_u8 (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtnl_unicast (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct net_device*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dcbnl_getfeatcfg(struct net_device *netdev, struct nlattr **tb,
			    u32 pid, u32 seq, u16 flags)
{
	struct sk_buff *dcbnl_skb;
	struct nlmsghdr *nlh;
	struct dcbmsg *dcb;
	struct nlattr *data[DCB_FEATCFG_ATTR_MAX + 1], *nest;
	u8 value;
	int ret, i;
	int getall = 0;

	if (!netdev->dcbnl_ops->getfeatcfg)
		return -EOPNOTSUPP;

	if (!tb[DCB_ATTR_FEATCFG])
		return -EINVAL;

	ret = nla_parse_nested(data, DCB_FEATCFG_ATTR_MAX, tb[DCB_ATTR_FEATCFG],
			       dcbnl_featcfg_nest);
	if (ret)
		goto err_out;

	dcbnl_skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!dcbnl_skb) {
		ret = -ENOBUFS;
		goto err_out;
	}

	nlh = NLMSG_NEW(dcbnl_skb, pid, seq, RTM_GETDCB, sizeof(*dcb), flags);

	dcb = NLMSG_DATA(nlh);
	dcb->dcb_family = AF_UNSPEC;
	dcb->cmd = DCB_CMD_GFEATCFG;

	nest = nla_nest_start(dcbnl_skb, DCB_ATTR_FEATCFG);
	if (!nest) {
		ret = -EMSGSIZE;
		goto nla_put_failure;
	}

	if (data[DCB_FEATCFG_ATTR_ALL])
		getall = 1;

	for (i = DCB_FEATCFG_ATTR_ALL+1; i <= DCB_FEATCFG_ATTR_MAX; i++) {
		if (!getall && !data[i])
			continue;

		ret = netdev->dcbnl_ops->getfeatcfg(netdev, i, &value);
		if (!ret)
			ret = nla_put_u8(dcbnl_skb, i, value);

		if (ret) {
			nla_nest_cancel(dcbnl_skb, nest);
			goto nla_put_failure;
		}
	}
	nla_nest_end(dcbnl_skb, nest);

	nlmsg_end(dcbnl_skb, nlh);

	return rtnl_unicast(dcbnl_skb, &init_net, pid);
nla_put_failure:
	nlmsg_cancel(dcbnl_skb, nlh);
nlmsg_failure:
	kfree_skb(dcbnl_skb);
err_out:
	return ret;
}