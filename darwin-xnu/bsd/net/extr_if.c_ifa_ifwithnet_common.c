#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct sockaddr_dl {int sdl_index; } ;
struct sockaddr {scalar_t__ sa_family; char* sa_data; } ;
struct TYPE_8__ {struct ifaddr* tqh_first; } ;
struct TYPE_7__ {struct ifnet* tqe_next; } ;
struct ifnet {unsigned int if_index; TYPE_2__ if_addrhead; TYPE_1__ if_link; } ;
struct TYPE_9__ {struct ifaddr* tqe_next; } ;
struct ifaddr {TYPE_5__* ifa_netmask; TYPE_4__* ifa_addr; TYPE_3__ ifa_link; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_12__ {struct ifnet* tqh_first; } ;
struct TYPE_11__ {char* sa_data; int sa_len; } ;
struct TYPE_10__ {scalar_t__ sa_family; char* sa_data; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_LINK ; 
 int /*<<< orphan*/  IFA_ADDREF (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_ADDREF_LOCKED (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_LOCK (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_LOCK_ASSERT_NOTHELD (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_REMREF (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 unsigned int IFSCOPE_NONE ; 
 int if_index ; 
 struct ifaddr** ifnet_addrs ; 
 TYPE_6__ ifnet_head ; 
 int /*<<< orphan*/  ifnet_head_done () ; 
 int /*<<< orphan*/  ifnet_head_lock_shared () ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (struct ifnet*) ; 
 scalar_t__ rn_refines (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ifaddr *
ifa_ifwithnet_common(const struct sockaddr *addr, unsigned int ifscope)
{
	struct ifnet *ifp;
	struct ifaddr *ifa = NULL;
	struct ifaddr *ifa_maybe = NULL;
	u_int af = addr->sa_family;
	const char *addr_data = addr->sa_data, *cplim;

#if INET6
	if (af != AF_INET && af != AF_INET6)
#else
	if (af != AF_INET)
#endif /* !INET6 */
		ifscope = IFSCOPE_NONE;

	ifnet_head_lock_shared();
	/*
	 * AF_LINK addresses can be looked up directly by their index number,
	 * so do that if we can.
	 */
	if (af == AF_LINK) {
		const struct sockaddr_dl *sdl =
		    (const struct sockaddr_dl *)(uintptr_t)(size_t)addr;
		if (sdl->sdl_index && sdl->sdl_index <= if_index) {
			ifa = ifnet_addrs[sdl->sdl_index - 1];
			if (ifa != NULL)
				IFA_ADDREF(ifa);

			ifnet_head_done();
			return (ifa);
		}
	}

	/*
	 * Scan though each interface, looking for ones that have
	 * addresses in this address family.
	 */
	for (ifp = ifnet_head.tqh_first; ifp; ifp = ifp->if_link.tqe_next) {
		ifnet_lock_shared(ifp);
		for (ifa = ifp->if_addrhead.tqh_first; ifa;
		     ifa = ifa->ifa_link.tqe_next) {
			const char *cp, *cp2, *cp3;

			IFA_LOCK(ifa);
			if (ifa->ifa_addr == NULL ||
			    ifa->ifa_addr->sa_family != af) {
next:
				IFA_UNLOCK(ifa);
				continue;
			}
			/*
			 * If we're looking up with a scope,
			 * find using a matching interface.
			 */
			if (ifscope != IFSCOPE_NONE &&
			    ifp->if_index != ifscope) {
				IFA_UNLOCK(ifa);
				continue;
			}

			/*
			 * Scan all the bits in the ifa's address.
			 * If a bit dissagrees with what we are
			 * looking for, mask it with the netmask
			 * to see if it really matters.
			 * (A byte at a time)
			 */
			if (ifa->ifa_netmask == 0) {
				IFA_UNLOCK(ifa);
				continue;
			}
			cp = addr_data;
			cp2 = ifa->ifa_addr->sa_data;
			cp3 = ifa->ifa_netmask->sa_data;
			cplim = ifa->ifa_netmask->sa_len +
			    (char *)ifa->ifa_netmask;
			while (cp3 < cplim)
				if ((*cp++ ^ *cp2++) & *cp3++)
					goto next; /* next address! */
			/*
			 * If the netmask of what we just found
			 * is more specific than what we had before
			 * (if we had one) then remember the new one
			 * before continuing to search
			 * for an even better one.
			 */
			if (ifa_maybe == NULL ||
			    rn_refines((caddr_t)ifa->ifa_netmask,
			    (caddr_t)ifa_maybe->ifa_netmask)) {
				IFA_ADDREF_LOCKED(ifa);	/* ifa_maybe */
				IFA_UNLOCK(ifa);
				if (ifa_maybe != NULL)
					IFA_REMREF(ifa_maybe);
				ifa_maybe = ifa;
			} else {
				IFA_UNLOCK(ifa);
			}
			IFA_LOCK_ASSERT_NOTHELD(ifa);
		}
		ifnet_lock_done(ifp);

		if (ifa != NULL)
			break;
	}
	ifnet_head_done();

	if (ifa == NULL)
		ifa = ifa_maybe;
	else if (ifa_maybe != NULL)
		IFA_REMREF(ifa_maybe);

	return (ifa);
}