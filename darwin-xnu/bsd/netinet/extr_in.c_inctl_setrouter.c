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
struct ifreq {int /*<<< orphan*/  ifr_intval; } ;
struct ifnet {int if_flags; int if_eflags; } ;
typedef  int /*<<< orphan*/  intval ;

/* Variables and functions */
 int ENODEV ; 
 int IFEF_ARPLL ; 
 int IFEF_AUTOCONFIGURING ; 
 int IFEF_IPV4_ROUTER ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int /*<<< orphan*/  in_purgeaddrs (struct ifnet*) ; 

__attribute__((used)) static __attribute__((noinline)) int
inctl_setrouter(struct ifnet *ifp, struct ifreq *ifr)
{
	int error = 0, intval;

	VERIFY(ifp != NULL);

	/* Router mode isn't valid for loopback */
	if (ifp->if_flags & IFF_LOOPBACK)
		return (ENODEV);

	bcopy(&ifr->ifr_intval, &intval, sizeof (intval));

	ifnet_lock_exclusive(ifp);
	if (intval) {
		ifp->if_eflags |= IFEF_IPV4_ROUTER;
		ifp->if_eflags &= ~(IFEF_ARPLL | IFEF_AUTOCONFIGURING);
	} else {
		ifp->if_eflags &= ~IFEF_IPV4_ROUTER;
	}
	ifnet_lock_done(ifp);

	/* purge all IPv4 addresses configured on this interface */
	in_purgeaddrs(ifp);

	return (error);
}