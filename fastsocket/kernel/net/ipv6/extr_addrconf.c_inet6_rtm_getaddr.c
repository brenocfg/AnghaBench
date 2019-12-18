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
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct inet6_ifaddr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifaddrmsg {scalar_t__ ifa_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IFA_ADDRESS ; 
 size_t IFA_LOCAL ; 
 int /*<<< orphan*/  IFA_MAX ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  RTM_NEWADDR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct net_device* __dev_get_by_index (struct net*,scalar_t__) ; 
 struct in6_addr* extract_addr (struct nlattr*,struct nlattr*) ; 
 int /*<<< orphan*/  ifa_ipv6_policy ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 int inet6_fill_ifaddr (struct sk_buff*,struct inet6_ifaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_ifaddr_msgsize () ; 
 struct inet6_ifaddr* ipv6_get_ifaddr (struct net*,struct in6_addr*,struct net_device*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct ifaddrmsg* nlmsg_data (struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet6_rtm_getaddr(struct sk_buff *in_skb, struct nlmsghdr* nlh,
			     void *arg)
{
	struct net *net = sock_net(in_skb->sk);
	struct ifaddrmsg *ifm;
	struct nlattr *tb[IFA_MAX+1];
	struct in6_addr *addr = NULL;
	struct net_device *dev = NULL;
	struct inet6_ifaddr *ifa;
	struct sk_buff *skb;
	int err;

	err = nlmsg_parse(nlh, sizeof(*ifm), tb, IFA_MAX, ifa_ipv6_policy);
	if (err < 0)
		goto errout;

	addr = extract_addr(tb[IFA_ADDRESS], tb[IFA_LOCAL]);
	if (addr == NULL) {
		err = -EINVAL;
		goto errout;
	}

	ifm = nlmsg_data(nlh);
	if (ifm->ifa_index)
		dev = __dev_get_by_index(net, ifm->ifa_index);

	if ((ifa = ipv6_get_ifaddr(net, addr, dev, 1)) == NULL) {
		err = -EADDRNOTAVAIL;
		goto errout;
	}

	if ((skb = nlmsg_new(inet6_ifaddr_msgsize(), GFP_KERNEL)) == NULL) {
		err = -ENOBUFS;
		goto errout_ifa;
	}

	err = inet6_fill_ifaddr(skb, ifa, NETLINK_CB(in_skb).pid,
				nlh->nlmsg_seq, RTM_NEWADDR, 0);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in inet6_ifaddr_msgsize() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout_ifa;
	}
	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).pid);
errout_ifa:
	in6_ifa_put(ifa);
errout:
	return err;
}