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
struct TYPE_2__ {scalar_t__ sin6_family; } ;
struct ifaddr {int dummy; } ;
struct in6_ifaddr {int ia_flags; int ia_plen; TYPE_1__ ia_dstaddr; struct ifaddr ia_ifa; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IFA_LOCK (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_LOCK_ASSERT_HELD (struct ifaddr*) ; 
 int IFA_ROUTE ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 int IN6_IFAUPDATE_1STADDR ; 
 int IN6_IFAUPDATE_NEWADDR ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int RTF_CLONING ; 
 int RTF_HOST ; 
 int RTF_UP ; 
 int /*<<< orphan*/  RTM_ADD ; 
 int /*<<< orphan*/  SIOCSIFADDR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ifnet_ioctl (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in6_ifaddr*) ; 
 int /*<<< orphan*/  in6_ifaddloop (struct ifaddr*) ; 
 int /*<<< orphan*/  routegenid_inet6_update () ; 
 int rtinit (struct ifaddr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
in6_ifinit(struct ifnet *ifp, struct in6_ifaddr *ia, int ifaupflags)
{
	int error;
	struct ifaddr *ifa;

	error = 0;
	ifa = &ia->ia_ifa;

	/*
	 * NOTE: SIOCSIFADDR is defined with struct ifreq as parameter,
	 * but here we are sending it down to the interface with a pointer
	 * to struct ifaddr, for legacy reasons.
	 */
	if ((ifaupflags & IN6_IFAUPDATE_1STADDR) != 0) {
		error = ifnet_ioctl(ifp, PF_INET6, SIOCSIFADDR, ia);
		if (error != 0) {
			if (error != EOPNOTSUPP)
				return (error);
			error = 0;
		}
	}

	IFA_LOCK(ifa);

	/*
	 * Special case:
	 * If the destination address is specified for a point-to-point
	 * interface, install a route to the destination as an interface
	 * direct route.
	 */
	if (!(ia->ia_flags & IFA_ROUTE) && ia->ia_plen == 128 &&
	    ia->ia_dstaddr.sin6_family == AF_INET6) {
		IFA_UNLOCK(ifa);
		error = rtinit(ifa, RTM_ADD, RTF_UP | RTF_HOST);
		if (error != 0)
			return (error);
		IFA_LOCK(ifa);
		ia->ia_flags |= IFA_ROUTE;
	}
	IFA_LOCK_ASSERT_HELD(ifa);
	if (ia->ia_plen < 128) {
		/*
		 * The RTF_CLONING flag is necessary for in6_is_ifloop_auto().
		 */
		ia->ia_flags |= RTF_CLONING;
	}

	IFA_UNLOCK(ifa);

	/* Add ownaddr as loopback rtentry, if necessary (ex. on p2p link). */
	if ((ifaupflags & IN6_IFAUPDATE_NEWADDR) != 0)
		in6_ifaddloop(ifa);

	/* invalidate route caches */
	routegenid_inet6_update();

	VERIFY(error == 0);
	return (0);
}