#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct ifnet* ifa_ifp; } ;
struct in6_ifaddr {int ia6_flags; struct in6_ifaddr* ia_next; TYPE_1__ ia_ifa; } ;
struct ifnet {int if_flags; int if_eflags; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IFA_ADDREF_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  IFA_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  IFA_REMREF (TYPE_1__*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (TYPE_1__*) ; 
 int IFEF_ACCEPT_RTADV ; 
 int IFEF_IPV6_ROUTER ; 
 int IFF_LOOPBACK ; 
 int IN6_IFF_AUTOCONF ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int /*<<< orphan*/  in6_ifaddr_rwlock ; 
 struct in6_ifaddr* in6_ifaddrs ; 
 int /*<<< orphan*/  in6_purgeaddr (TYPE_1__*) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __attribute__((noinline)) int
in6_autoconf(struct ifnet *ifp, int enable)
{
	int error = 0;

	VERIFY(ifp != NULL);

	if (ifp->if_flags & IFF_LOOPBACK)
		return (EINVAL);

	if (enable) {
		/*
		 * An interface in IPv6 router mode implies that it
		 * is either configured with a static IP address or
		 * autoconfigured via a locally-generated RA.  Prevent
		 * SIOCAUTOCONF_START from being set in that mode.
		 */
		ifnet_lock_exclusive(ifp);
		if (ifp->if_eflags & IFEF_IPV6_ROUTER) {
			ifp->if_eflags &= ~IFEF_ACCEPT_RTADV;
			error = EBUSY;
		} else {
			ifp->if_eflags |= IFEF_ACCEPT_RTADV;
		}
		ifnet_lock_done(ifp);
	} else {
		struct in6_ifaddr *ia = NULL;

		ifnet_lock_exclusive(ifp);
		ifp->if_eflags &= ~IFEF_ACCEPT_RTADV;
		ifnet_lock_done(ifp);

		/* Remove autoconfigured address from interface */
		lck_rw_lock_exclusive(&in6_ifaddr_rwlock);
		ia = in6_ifaddrs;
		while (ia != NULL) {
			if (ia->ia_ifa.ifa_ifp != ifp) {
				ia = ia->ia_next;
				continue;
			}
			IFA_LOCK(&ia->ia_ifa);
			if (ia->ia6_flags & IN6_IFF_AUTOCONF) {
				IFA_ADDREF_LOCKED(&ia->ia_ifa);	/* for us */
				IFA_UNLOCK(&ia->ia_ifa);
				lck_rw_done(&in6_ifaddr_rwlock);
				in6_purgeaddr(&ia->ia_ifa);
				IFA_REMREF(&ia->ia_ifa);	/* for us */
				lck_rw_lock_exclusive(&in6_ifaddr_rwlock);
				/*
				 * Purging the address caused in6_ifaddr_rwlock
				 * to be dropped and reacquired;
				 * therefore search again from the beginning
				 * of in6_ifaddrs list.
				 */
				ia = in6_ifaddrs;
				continue;
			}
			IFA_UNLOCK(&ia->ia_ifa);
			ia = ia->ia_next;
		}
		lck_rw_done(&in6_ifaddr_rwlock);
	}
	return (error);
}