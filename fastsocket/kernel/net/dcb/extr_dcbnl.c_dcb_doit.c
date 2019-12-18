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
struct nlmsghdr {int /*<<< orphan*/  nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct net_device {int /*<<< orphan*/  dcbnl_ops; } ;
struct net {int dummy; } ;
struct dcbmsg {int cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 size_t DCB_ATTR_IFNAME ; 
 int /*<<< orphan*/  DCB_ATTR_MAX ; 
#define  DCB_CMD_BCN_GCFG 154 
#define  DCB_CMD_BCN_SCFG 153 
#define  DCB_CMD_CEE_GET 152 
#define  DCB_CMD_GAPP 151 
#define  DCB_CMD_GCAP 150 
#define  DCB_CMD_GDCBX 149 
#define  DCB_CMD_GFEATCFG 148 
#define  DCB_CMD_GNUMTCS 147 
#define  DCB_CMD_GPERM_HWADDR 146 
#define  DCB_CMD_GSTATE 145 
#define  DCB_CMD_IEEE_DEL 144 
#define  DCB_CMD_IEEE_GET 143 
#define  DCB_CMD_IEEE_SET 142 
#define  DCB_CMD_PFC_GCFG 141 
#define  DCB_CMD_PFC_GSTATE 140 
#define  DCB_CMD_PFC_SCFG 139 
#define  DCB_CMD_PFC_SSTATE 138 
#define  DCB_CMD_PGRX_GCFG 137 
#define  DCB_CMD_PGRX_SCFG 136 
#define  DCB_CMD_PGTX_GCFG 135 
#define  DCB_CMD_PGTX_SCFG 134 
#define  DCB_CMD_SAPP 133 
#define  DCB_CMD_SDCBX 132 
#define  DCB_CMD_SET_ALL 131 
#define  DCB_CMD_SFEATCFG 130 
#define  DCB_CMD_SNUMTCS 129 
#define  DCB_CMD_SSTATE 128 
 int EINVAL ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 scalar_t__ NLMSG_DATA (struct nlmsghdr*) ; 
 int dcbnl_bcn_getcfg (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_bcn_setcfg (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_cee_get (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_getapp (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_getcap (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_getdcbx (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_getfeatcfg (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_getnumtcs (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_getperm_hwaddr (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_getpfccfg (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_getpfcstate (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_getstate (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_ieee_del (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_ieee_get (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_ieee_set (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_pgrx_getcfg (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_pgrx_setcfg (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_pgtx_getcfg (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_pgtx_setcfg (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcbnl_rtnl_policy ; 
 int dcbnl_setall (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_setapp (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_setdcbx (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_setfeatcfg (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_setnumtcs (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_setpfccfg (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_setpfcstate (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcbnl_setstate (struct net_device*,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcb_doit(struct sk_buff *skb, struct nlmsghdr *nlh, void *arg)
{
	struct net *net = sock_net(skb->sk);
	struct net_device *netdev;
	struct dcbmsg  *dcb = (struct dcbmsg *)NLMSG_DATA(nlh);
	struct nlattr *tb[DCB_ATTR_MAX + 1];
	u32 pid = skb ? NETLINK_CB(skb).pid : 0;
	int ret = -EINVAL;

	if (!net_eq(net, &init_net))
		return -EINVAL;

	ret = nlmsg_parse(nlh, sizeof(*dcb), tb, DCB_ATTR_MAX,
			  dcbnl_rtnl_policy);
	if (ret < 0)
		return ret;

	if (!tb[DCB_ATTR_IFNAME])
		return -EINVAL;

	netdev = dev_get_by_name(&init_net, nla_data(tb[DCB_ATTR_IFNAME]));
	if (!netdev)
		return -EINVAL;

	if (!netdev->dcbnl_ops)
		goto errout;

	switch (dcb->cmd) {
	case DCB_CMD_GSTATE:
		ret = dcbnl_getstate(netdev, tb, pid, nlh->nlmsg_seq,
		                     nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_PFC_GCFG:
		ret = dcbnl_getpfccfg(netdev, tb, pid, nlh->nlmsg_seq,
		                      nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_GPERM_HWADDR:
		ret = dcbnl_getperm_hwaddr(netdev, tb, pid, nlh->nlmsg_seq,
		                           nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_PGTX_GCFG:
		ret = dcbnl_pgtx_getcfg(netdev, tb, pid, nlh->nlmsg_seq,
		                        nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_PGRX_GCFG:
		ret = dcbnl_pgrx_getcfg(netdev, tb, pid, nlh->nlmsg_seq,
		                        nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_BCN_GCFG:
		ret = dcbnl_bcn_getcfg(netdev, tb, pid, nlh->nlmsg_seq,
		                       nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_SSTATE:
		ret = dcbnl_setstate(netdev, tb, pid, nlh->nlmsg_seq,
		                     nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_PFC_SCFG:
		ret = dcbnl_setpfccfg(netdev, tb, pid, nlh->nlmsg_seq,
		                      nlh->nlmsg_flags);
		goto out;

	case DCB_CMD_SET_ALL:
		ret = dcbnl_setall(netdev, tb, pid, nlh->nlmsg_seq,
		                   nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_PGTX_SCFG:
		ret = dcbnl_pgtx_setcfg(netdev, tb, pid, nlh->nlmsg_seq,
		                        nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_PGRX_SCFG:
		ret = dcbnl_pgrx_setcfg(netdev, tb, pid, nlh->nlmsg_seq,
		                        nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_GCAP:
		ret = dcbnl_getcap(netdev, tb, pid, nlh->nlmsg_seq,
		                   nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_GNUMTCS:
		ret = dcbnl_getnumtcs(netdev, tb, pid, nlh->nlmsg_seq,
		                      nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_SNUMTCS:
		ret = dcbnl_setnumtcs(netdev, tb, pid, nlh->nlmsg_seq,
		                      nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_PFC_GSTATE:
		ret = dcbnl_getpfcstate(netdev, tb, pid, nlh->nlmsg_seq,
		                        nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_PFC_SSTATE:
		ret = dcbnl_setpfcstate(netdev, tb, pid, nlh->nlmsg_seq,
		                        nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_BCN_SCFG:
		ret = dcbnl_bcn_setcfg(netdev, tb, pid, nlh->nlmsg_seq,
		                       nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_GAPP:
		ret = dcbnl_getapp(netdev, tb, pid, nlh->nlmsg_seq,
		                   nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_SAPP:
		ret = dcbnl_setapp(netdev, tb, pid, nlh->nlmsg_seq,
		                   nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_IEEE_SET:
		ret = dcbnl_ieee_set(netdev, tb, pid, nlh->nlmsg_seq,
				     nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_IEEE_GET:
		ret = dcbnl_ieee_get(netdev, tb, pid, nlh->nlmsg_seq,
				     nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_IEEE_DEL:
		ret = dcbnl_ieee_del(netdev, tb, pid, nlh->nlmsg_seq,
				     nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_GDCBX:
		ret = dcbnl_getdcbx(netdev, tb, pid, nlh->nlmsg_seq,
				    nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_SDCBX:
		ret = dcbnl_setdcbx(netdev, tb, pid, nlh->nlmsg_seq,
				    nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_GFEATCFG:
		ret = dcbnl_getfeatcfg(netdev, tb, pid, nlh->nlmsg_seq,
				       nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_SFEATCFG:
		ret = dcbnl_setfeatcfg(netdev, tb, pid, nlh->nlmsg_seq,
				       nlh->nlmsg_flags);
		goto out;
	case DCB_CMD_CEE_GET:
		ret = dcbnl_cee_get(netdev, tb, pid, nlh->nlmsg_seq,
				    nlh->nlmsg_flags);
		goto out;
	default:
		goto errout;
	}
errout:
	ret = -EINVAL;
out:
	dev_put(netdev);
	return ret;
}