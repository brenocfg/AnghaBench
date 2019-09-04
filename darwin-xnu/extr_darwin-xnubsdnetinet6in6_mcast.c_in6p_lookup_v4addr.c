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
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct ipv6_mreq {unsigned int ipv6mr_interface; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct ip_mreq {TYPE_1__ imr_interface; } ;
struct ifnet {int dummy; } ;
struct ifaddr {scalar_t__ ifa_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  IFA_REMREF (struct ifaddr*) ; 
 scalar_t__ if_index ; 
 struct ifaddr* ifa_ifpgetprimary (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct ifnet** ifindex2ifnet ; 
 int /*<<< orphan*/  ifnet_head_done () ; 
 int /*<<< orphan*/  ifnet_head_lock_shared () ; 

__attribute__((used)) static int
in6p_lookup_v4addr(struct ipv6_mreq *mreq, struct ip_mreq *v4mreq)
{
	struct ifnet *ifp;
	struct ifaddr *ifa;
	struct sockaddr_in *sin;

	ifnet_head_lock_shared();
	if (mreq->ipv6mr_interface > (unsigned int)if_index) {
		ifnet_head_done();
		return (EADDRNOTAVAIL);
	} else
		ifp = ifindex2ifnet[mreq->ipv6mr_interface];
	ifnet_head_done();
	if (ifp == NULL)
		return (EADDRNOTAVAIL);
	ifa = ifa_ifpgetprimary(ifp, AF_INET);
	if (ifa == NULL)
		return (EADDRNOTAVAIL);
	sin = (struct sockaddr_in *)(uintptr_t)(size_t)ifa->ifa_addr;
	v4mreq->imr_interface.s_addr = sin->sin_addr.s_addr;
	IFA_REMREF(ifa);

	return (0);
}