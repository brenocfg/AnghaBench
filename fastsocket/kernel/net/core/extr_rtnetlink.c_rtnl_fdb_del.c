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
struct nlattr {int dummy; } ;
struct net_device {int priv_flags; } ;
struct net {int dummy; } ;
struct ndmsg {scalar_t__ ndm_ifindex; int ndm_flags; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int (* ndo_fdb_del ) (struct ndmsg*,struct nlattr**,struct net_device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ ETH_ALEN ; 
 int IFF_BRIDGE_PORT ; 
 size_t NDA_LLADDR ; 
 int /*<<< orphan*/  NDA_MAX ; 
 int NTF_MASTER ; 
 int NTF_SELF ; 
 int /*<<< orphan*/  RTM_DELNEIGH ; 
 struct net_device* __dev_get_by_index (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_extended (struct net_device*) ; 
 int /*<<< orphan*/ * nla_data (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 
 struct ndmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  rtnl_fdb_notify (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int stub1 (struct ndmsg*,struct nlattr**,struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtnl_fdb_del(struct sk_buff *skb, struct nlmsghdr *nlh, void *arg)
{
	struct net *net = sock_net(skb->sk);
	struct ndmsg *ndm;
	struct nlattr *tb[NDA_MAX+1];
	struct net_device *dev;
	int err = -EINVAL;
	__u8 *addr;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	err = nlmsg_parse(nlh, sizeof(*ndm), tb, NDA_MAX, NULL);
	if (err < 0)
		return err;

	ndm = nlmsg_data(nlh);
	if (ndm->ndm_ifindex == 0) {
		pr_info("PF_BRIDGE: RTM_DELNEIGH with invalid ifindex\n");
		return -EINVAL;
	}

	dev = __dev_get_by_index(net, ndm->ndm_ifindex);
	if (dev == NULL) {
		pr_info("PF_BRIDGE: RTM_DELNEIGH with unknown ifindex\n");
		return -ENODEV;
	}

	if (!tb[NDA_LLADDR] || nla_len(tb[NDA_LLADDR]) != ETH_ALEN) {
		pr_info("PF_BRIDGE: RTM_DELNEIGH with invalid address\n");
		return -EINVAL;
	}

	addr = nla_data(tb[NDA_LLADDR]);

	err = -EOPNOTSUPP;

	/* Support fdb on master device the net/bridge default case */
	if ((!ndm->ndm_flags || ndm->ndm_flags & NTF_MASTER) &&
	    (dev->priv_flags & IFF_BRIDGE_PORT)) {
		ndm->ndm_flags &= ~NTF_MASTER;
	}

	/* Embedded bridge, macvlan, and any other device support */
	if ((ndm->ndm_flags & NTF_SELF) && netdev_extended(dev)->ndo_fdb_del) {
		err = netdev_extended(dev)->ndo_fdb_del(ndm, tb, dev, addr);

		if (!err) {
			rtnl_fdb_notify(dev, addr, RTM_DELNEIGH);
			ndm->ndm_flags &= ~NTF_SELF;
		}
	}

	return err;
}