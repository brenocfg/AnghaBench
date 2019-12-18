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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct in_device {TYPE_1__ cnf; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENODATA ; 
 int /*<<< orphan*/  IFLA_INET_CONF ; 
 int IPV4_DEVCONF_MAX ; 
 struct in_device* __in_dev_get_rtnl (struct net_device const*) ; 
 scalar_t__ nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int inet_fill_link_af(struct sk_buff *skb, const struct net_device *dev)
{
	struct in_device *in_dev = __in_dev_get_rtnl(dev);
	struct nlattr *nla;
	int i;

	if (!in_dev)
		return -ENODATA;

	nla = nla_reserve(skb, IFLA_INET_CONF, IPV4_DEVCONF_MAX * 4);
	if (nla == NULL)
		return -EMSGSIZE;

	for (i = 0; i < IPV4_DEVCONF_MAX; i++)
		((u32 *) nla_data(nla))[i] = in_dev->cnf.data[i];

	return 0;
}