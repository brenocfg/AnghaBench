#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct inet6_ifaddr {int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {scalar_t__ optimistic_dad; } ;
struct inet6_dev {int /*<<< orphan*/  dev; TYPE_1__ cnf; } ;
struct in6_addr {int dummy; } ;
struct TYPE_7__ {TYPE_2__* devconf_all; } ;
struct TYPE_8__ {TYPE_3__ ipv6; } ;
struct TYPE_6__ {int /*<<< orphan*/  forwarding; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_F_OPTIMISTIC ; 
 int /*<<< orphan*/  IFA_F_PERMANENT ; 
 int /*<<< orphan*/  IFA_LINK ; 
 int /*<<< orphan*/  IS_ERR (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_dad_start (struct inet6_ifaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addrconf_prefix_route (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 struct inet6_ifaddr* ipv6_add_addr (struct inet6_dev*,struct in6_addr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void addrconf_add_linklocal(struct inet6_dev *idev, struct in6_addr *addr)
{
	struct inet6_ifaddr * ifp;
	u32 addr_flags = IFA_F_PERMANENT;

#ifdef CONFIG_IPV6_OPTIMISTIC_DAD
	if (idev->cnf.optimistic_dad &&
	    !dev_net(idev->dev)->ipv6.devconf_all->forwarding)
		addr_flags |= IFA_F_OPTIMISTIC;
#endif


	ifp = ipv6_add_addr(idev, addr, 64, IFA_LINK, addr_flags, 0, 0);
	if (!IS_ERR(ifp)) {
		addrconf_prefix_route(&ifp->addr, ifp->prefix_len, idev->dev, 0, 0);
		addrconf_dad_start(ifp, 0);
		in6_ifa_put(ifp);
	}
}