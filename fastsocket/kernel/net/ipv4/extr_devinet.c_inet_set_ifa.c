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
struct net_device {int dummy; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_scope; int /*<<< orphan*/  ifa_local; struct in_device* ifa_dev; } ;
struct in_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  RT_SCOPE_HOST ; 
 int /*<<< orphan*/  WARN_ON (struct in_device*) ; 
 struct in_device* __in_dev_get_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  in_dev_hold (struct in_device*) ; 
 int /*<<< orphan*/  inet_free_ifa (struct in_ifaddr*) ; 
 int inet_insert_ifa (struct in_ifaddr*) ; 
 int /*<<< orphan*/  ipv4_devconf_setall (struct in_device*) ; 
 scalar_t__ ipv4_is_loopback (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet_set_ifa(struct net_device *dev, struct in_ifaddr *ifa)
{
	struct in_device *in_dev = __in_dev_get_rtnl(dev);

	ASSERT_RTNL();

	if (!in_dev) {
		inet_free_ifa(ifa);
		return -ENOBUFS;
	}
	ipv4_devconf_setall(in_dev);
	if (ifa->ifa_dev != in_dev) {
		WARN_ON(ifa->ifa_dev);
		in_dev_hold(in_dev);
		ifa->ifa_dev = in_dev;
	}
	if (ipv4_is_loopback(ifa->ifa_local))
		ifa->ifa_scope = RT_SCOPE_HOST;
	return inet_insert_ifa(ifa);
}