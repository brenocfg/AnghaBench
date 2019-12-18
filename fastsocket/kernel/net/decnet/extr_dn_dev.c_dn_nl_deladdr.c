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
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct ifaddrmsg {int /*<<< orphan*/  ifa_index; } ;
struct dn_ifaddr {int /*<<< orphan*/  ifa_label; int /*<<< orphan*/  ifa_local; struct dn_ifaddr* ifa_next; } ;
struct dn_dev {struct dn_ifaddr* ifa_list; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ENODEV ; 
 size_t IFA_LABEL ; 
 size_t IFA_LOCAL ; 
 int /*<<< orphan*/  IFA_MAX ; 
 struct dn_dev* dn_dev_by_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_dev_del_ifa (struct dn_dev*,struct dn_ifaddr**,int) ; 
 int /*<<< orphan*/  dn_ifa_policy ; 
 struct net init_net ; 
 scalar_t__ nla_memcmp (struct nlattr*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ nla_strcmp (struct nlattr*,int /*<<< orphan*/ ) ; 
 struct ifaddrmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dn_nl_deladdr(struct sk_buff *skb, struct nlmsghdr *nlh, void *arg)
{
	struct net *net = sock_net(skb->sk);
	struct nlattr *tb[IFA_MAX+1];
	struct dn_dev *dn_db;
	struct ifaddrmsg *ifm;
	struct dn_ifaddr *ifa, **ifap;
	int err = -EINVAL;

	if (net != &init_net)
		goto errout;

	err = nlmsg_parse(nlh, sizeof(*ifm), tb, IFA_MAX, dn_ifa_policy);
	if (err < 0)
		goto errout;

	err = -ENODEV;
	ifm = nlmsg_data(nlh);
	if ((dn_db = dn_dev_by_index(ifm->ifa_index)) == NULL)
		goto errout;

	err = -EADDRNOTAVAIL;
	for (ifap = &dn_db->ifa_list; (ifa = *ifap); ifap = &ifa->ifa_next) {
		if (tb[IFA_LOCAL] &&
		    nla_memcmp(tb[IFA_LOCAL], &ifa->ifa_local, 2))
			continue;

		if (tb[IFA_LABEL] && nla_strcmp(tb[IFA_LABEL], ifa->ifa_label))
			continue;

		dn_dev_del_ifa(dn_db, ifap, 1);
		return 0;
	}

errout:
	return err;
}