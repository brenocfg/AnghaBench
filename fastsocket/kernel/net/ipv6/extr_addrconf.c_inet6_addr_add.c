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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct inet6_ifaddr {int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; } ;
struct inet6_dev {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  scalar_t__ clock_t ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  unsigned long __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENODEV ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  IFA_F_DEPRECATED ; 
 int /*<<< orphan*/  IFA_F_PERMANENT ; 
 int /*<<< orphan*/  IS_ERR (struct inet6_ifaddr*) ; 
 int PTR_ERR (struct inet6_ifaddr*) ; 
 scalar_t__ RTF_EXPIRES ; 
 struct net_device* __dev_get_by_index (struct net*,int) ; 
 struct inet6_dev* addrconf_add_dev (struct net_device*) ; 
 int /*<<< orphan*/  addrconf_dad_start (struct inet6_ifaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ addrconf_finite_timeout (unsigned long) ; 
 int /*<<< orphan*/  addrconf_prefix_route (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct net_device*,scalar_t__,scalar_t__) ; 
 unsigned long addrconf_timeout_fixup (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  addrconf_verify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 struct inet6_ifaddr* ipv6_add_addr (struct inet6_dev*,struct in6_addr*,unsigned int,int,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int ipv6_addr_scope (struct in6_addr*) ; 
 scalar_t__ jiffies_to_clock_t (unsigned long) ; 

__attribute__((used)) static int inet6_addr_add(struct net *net, int ifindex, struct in6_addr *pfx,
			  unsigned int plen, __u8 ifa_flags, __u32 prefered_lft,
			  __u32 valid_lft)
{
	struct inet6_ifaddr *ifp;
	struct inet6_dev *idev;
	struct net_device *dev;
	int scope;
	u32 flags;
	clock_t expires;
	unsigned long timeout;

	ASSERT_RTNL();

	if (plen > 128)
		return -EINVAL;

	/* check the lifetime */
	if (!valid_lft || prefered_lft > valid_lft)
		return -EINVAL;

	dev = __dev_get_by_index(net, ifindex);
	if (!dev)
		return -ENODEV;

	if ((idev = addrconf_add_dev(dev)) == NULL)
		return -ENOBUFS;

	scope = ipv6_addr_scope(pfx);

	timeout = addrconf_timeout_fixup(valid_lft, HZ);
	if (addrconf_finite_timeout(timeout)) {
		expires = jiffies_to_clock_t(timeout * HZ);
		valid_lft = timeout;
		flags = RTF_EXPIRES;
	} else {
		expires = 0;
		flags = 0;
		ifa_flags |= IFA_F_PERMANENT;
	}

	timeout = addrconf_timeout_fixup(prefered_lft, HZ);
	if (addrconf_finite_timeout(timeout)) {
		if (timeout == 0)
			ifa_flags |= IFA_F_DEPRECATED;
		prefered_lft = timeout;
	}

	ifp = ipv6_add_addr(idev, pfx, plen, scope, ifa_flags, valid_lft,
			    prefered_lft);

	if (!IS_ERR(ifp)) {
		addrconf_prefix_route(&ifp->addr, ifp->prefix_len, dev,
				      expires, flags);
		/*
		 * Note that section 3.1 of RFC 4429 indicates
		 * that the Optimistic flag should not be set for
		 * manually configured addresses
		 */
		addrconf_dad_start(ifp, 0);
		in6_ifa_put(ifp);
		addrconf_verify(0);
		return 0;
	}

	return PTR_ERR(ifp);
}