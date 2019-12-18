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
typedef  int u_long ;
struct sockaddr_in6 {int dummy; } ;
struct in6_ifreq {struct sockaddr_in6 ifr_dstaddr; struct sockaddr_in6 ifr_addr; } ;
struct in6_ifaddr {int /*<<< orphan*/  ia_ifa; struct sockaddr_in6 ia_dstaddr; struct sockaddr_in6 ia_addr; } ;
struct ifnet {int if_flags; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int /*<<< orphan*/  IFA_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFA_UNLOCK (int /*<<< orphan*/ *) ; 
 int IFF_POINTOPOINT ; 
#define  SIOCGIFADDR_IN6 129 
#define  SIOCGIFDSTADDR_IN6 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct sockaddr_in6*,struct sockaddr_in6*,int) ; 
 int sa6_recoverscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __attribute__((noinline)) int
in6ctl_gifaddr(struct ifnet *ifp, struct in6_ifaddr *ia, u_long cmd,
    struct in6_ifreq *ifr)
{
	struct sockaddr_in6 addr;
	int error = 0;

	VERIFY(ifp != NULL);

	if (ia == NULL)
		return (EADDRNOTAVAIL);

	switch (cmd) {
	case SIOCGIFADDR_IN6:		/* struct in6_ifreq */
		IFA_LOCK(&ia->ia_ifa);
		bcopy(&ia->ia_addr, &addr, sizeof (addr));
		IFA_UNLOCK(&ia->ia_ifa);
		if ((error = sa6_recoverscope(&addr, TRUE)) != 0)
			break;
		bcopy(&addr, &ifr->ifr_addr, sizeof (addr));
		break;

	case SIOCGIFDSTADDR_IN6:	/* struct in6_ifreq */
		if (!(ifp->if_flags & IFF_POINTOPOINT)) {
			error = EINVAL;
			break;
		}
		/*
		 * XXX: should we check if ifa_dstaddr is NULL and return
		 * an error?
		 */
		IFA_LOCK(&ia->ia_ifa);
		bcopy(&ia->ia_dstaddr, &addr, sizeof (addr));
		IFA_UNLOCK(&ia->ia_ifa);
		if ((error = sa6_recoverscope(&addr, TRUE)) != 0)
			break;
		bcopy(&addr, &ifr->ifr_dstaddr, sizeof (addr));
		break;

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}