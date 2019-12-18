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
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_type; int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifaddrlblmsg {scalar_t__ ifal_family; int ifal_prefixlen; scalar_t__ ifal_index; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t IFAL_ADDRESS ; 
 size_t IFAL_LABEL ; 
 int /*<<< orphan*/  IFAL_MAX ; 
 scalar_t__ IPV6_ADDR_LABEL_DEFAULT ; 
 int NLM_F_REPLACE ; 
#define  RTM_DELADDRLABEL 129 
#define  RTM_NEWADDRLABEL 128 
 int /*<<< orphan*/  __dev_get_by_index (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  ifal_policy ; 
 int ip6addrlbl_add (struct net*,struct in6_addr*,int,scalar_t__,scalar_t__,int) ; 
 int ip6addrlbl_del (struct net*,struct in6_addr*,int,scalar_t__) ; 
 struct in6_addr* nla_data (struct nlattr*) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 struct ifaddrlblmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip6addrlbl_newdel(struct sk_buff *skb, struct nlmsghdr *nlh,
			     void *arg)
{
	struct net *net = sock_net(skb->sk);
	struct ifaddrlblmsg *ifal;
	struct nlattr *tb[IFAL_MAX+1];
	struct in6_addr *pfx;
	u32 label;
	int err = 0;

	err = nlmsg_parse(nlh, sizeof(*ifal), tb, IFAL_MAX, ifal_policy);
	if (err < 0)
		return err;

	ifal = nlmsg_data(nlh);

	if (ifal->ifal_family != AF_INET6 ||
	    ifal->ifal_prefixlen > 128)
		return -EINVAL;

	if (ifal->ifal_index &&
	    !__dev_get_by_index(net, ifal->ifal_index))
		return -EINVAL;

	if (!tb[IFAL_ADDRESS])
		return -EINVAL;

	pfx = nla_data(tb[IFAL_ADDRESS]);
	if (!pfx)
		return -EINVAL;

	if (!tb[IFAL_LABEL])
		return -EINVAL;
	label = nla_get_u32(tb[IFAL_LABEL]);
	if (label == IPV6_ADDR_LABEL_DEFAULT)
		return -EINVAL;

	switch(nlh->nlmsg_type) {
	case RTM_NEWADDRLABEL:
		err = ip6addrlbl_add(net, pfx, ifal->ifal_prefixlen,
				     ifal->ifal_index, label,
				     nlh->nlmsg_flags & NLM_F_REPLACE);
		break;
	case RTM_DELADDRLABEL:
		err = ip6addrlbl_del(net, pfx, ifal->ifal_prefixlen,
				     ifal->ifal_index);
		break;
	default:
		err = -EOPNOTSUPP;
	}
	return err;
}