#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct ip6addrlbl_entry {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifaddrlblmsg {scalar_t__ ifal_family; int ifal_prefixlen; scalar_t__ ifal_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int ESRCH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IFAL_ADDRESS ; 
 int /*<<< orphan*/  IFAL_MAX ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  RTM_NEWADDRLABEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __dev_get_by_index (struct net*,scalar_t__) ; 
 struct ip6addrlbl_entry* __ipv6_addr_label (struct net*,struct in6_addr*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ifal_policy ; 
 int ip6addrlbl_fill (struct sk_buff*,struct ip6addrlbl_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ip6addrlbl_hold (struct ip6addrlbl_entry*) ; 
 int /*<<< orphan*/  ip6addrlbl_msgsize () ; 
 int /*<<< orphan*/  ip6addrlbl_put (struct ip6addrlbl_entry*) ; 
 TYPE_1__ ip6addrlbl_table ; 
 int /*<<< orphan*/  ipv6_addr_type (struct in6_addr*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct in6_addr* nla_data (struct nlattr*) ; 
 struct ifaddrlblmsg* nlmsg_data (struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip6addrlbl_get(struct sk_buff *in_skb, struct nlmsghdr* nlh,
			  void *arg)
{
	struct net *net = sock_net(in_skb->sk);
	struct ifaddrlblmsg *ifal;
	struct nlattr *tb[IFAL_MAX+1];
	struct in6_addr *addr;
	u32 lseq;
	int err = 0;
	struct ip6addrlbl_entry *p;
	struct sk_buff *skb;

	err = nlmsg_parse(nlh, sizeof(*ifal), tb, IFAL_MAX, ifal_policy);
	if (err < 0)
		return err;

	ifal = nlmsg_data(nlh);

	if (ifal->ifal_family != AF_INET6 ||
	    ifal->ifal_prefixlen != 128)
		return -EINVAL;

	if (ifal->ifal_index &&
	    !__dev_get_by_index(net, ifal->ifal_index))
		return -EINVAL;

	if (!tb[IFAL_ADDRESS])
		return -EINVAL;

	addr = nla_data(tb[IFAL_ADDRESS]);
	if (!addr)
		return -EINVAL;

	rcu_read_lock();
	p = __ipv6_addr_label(net, addr, ipv6_addr_type(addr), ifal->ifal_index);
	if (p && ip6addrlbl_hold(p))
		p = NULL;
	lseq = ip6addrlbl_table.seq;
	rcu_read_unlock();

	if (!p) {
		err = -ESRCH;
		goto out;
	}

	if (!(skb = nlmsg_new(ip6addrlbl_msgsize(), GFP_KERNEL))) {
		ip6addrlbl_put(p);
		return -ENOBUFS;
	}

	err = ip6addrlbl_fill(skb, p, lseq,
			      NETLINK_CB(in_skb).pid, nlh->nlmsg_seq,
			      RTM_NEWADDRLABEL, 0);

	ip6addrlbl_put(p);

	if (err < 0) {
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto out;
	}

	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).pid);
out:
	return err;
}