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
typedef  int u8 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {scalar_t__ nlmsg_type; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ifaddrmsg {int /*<<< orphan*/  ifa_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 size_t IFA_LOCAL ; 
 int /*<<< orphan*/  IFA_MAX ; 
 scalar_t__ RTM_NEWADDR ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifa_phonet_policy ; 
 int nla_get_u8 (struct nlattr*) ; 
 struct ifaddrmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phonet_address_add (struct net_device*,int) ; 
 int phonet_address_del (struct net_device*,int) ; 
 int /*<<< orphan*/  phonet_address_notify (scalar_t__,struct net_device*,int) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int addr_doit(struct sk_buff *skb, struct nlmsghdr *nlh, void *attr)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *tb[IFA_MAX+1];
	struct net_device *dev;
	struct ifaddrmsg *ifm;
	int err;
	u8 pnaddr;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	ASSERT_RTNL();

	err = nlmsg_parse(nlh, sizeof(*ifm), tb, IFA_MAX, ifa_phonet_policy);
	if (err < 0)
		return err;

	ifm = nlmsg_data(nlh);
	if (tb[IFA_LOCAL] == NULL)
		return -EINVAL;
	pnaddr = nla_get_u8(tb[IFA_LOCAL]);
	if (pnaddr & 3)
		/* Phonet addresses only have 6 high-order bits */
		return -EINVAL;

	dev = __dev_get_by_index(net, ifm->ifa_index);
	if (dev == NULL)
		return -ENODEV;

	if (nlh->nlmsg_type == RTM_NEWADDR)
		err = phonet_address_add(dev, pnaddr);
	else
		err = phonet_address_del(dev, pnaddr);
	if (!err)
		phonet_address_notify(nlh->nlmsg_type, dev, pnaddr);
	return err;
}