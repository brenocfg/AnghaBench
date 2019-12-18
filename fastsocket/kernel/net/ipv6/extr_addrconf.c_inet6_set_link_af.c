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
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct inet6_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  IFLA_INET6_MAX ; 
 size_t IFLA_INET6_TOKEN ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int inet6_set_iftoken (struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 scalar_t__ nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inet6_set_link_af(struct net_device *dev, const struct nlattr *nla)
{
	int err = -EINVAL;
	struct inet6_dev *idev = __in6_dev_get(dev);
	struct nlattr *tb[IFLA_INET6_MAX + 1];

	if (!idev)
		return -EAFNOSUPPORT;

	if (nla_parse_nested(tb, IFLA_INET6_MAX, nla, NULL) < 0)
		BUG();

	if (tb[IFLA_INET6_TOKEN])
		err = inet6_set_iftoken(idev, nla_data(tb[IFLA_INET6_TOKEN]));

	return err;
}