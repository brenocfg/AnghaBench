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
struct sockaddr {scalar_t__ sa_family; scalar_t__ sa_len; } ;
struct TYPE_6__ {struct ifaddr* tqh_first; } ;
struct TYPE_5__ {struct ifnet* tqe_next; } ;
struct ifnet {int if_flags; TYPE_2__ if_addrhead; TYPE_1__ if_link; } ;
struct TYPE_7__ {struct ifaddr* tqe_next; } ;
struct ifaddr {struct sockaddr const* ifa_broadaddr; struct sockaddr const* ifa_addr; TYPE_3__ ifa_link; } ;
struct TYPE_8__ {struct ifnet* tqh_first; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_ADDREF_LOCKED (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_LOCK_SPIN (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 int IFF_BROADCAST ; 
 scalar_t__ ifa_equal (struct sockaddr const*,struct sockaddr const*) ; 
 TYPE_4__ ifnet_head ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (struct ifnet*) ; 

struct ifaddr *
ifa_ifwithaddr_locked(const struct sockaddr *addr)
{
	struct ifnet *ifp;
	struct ifaddr *ifa;
	struct ifaddr *result = NULL;

	for (ifp = ifnet_head.tqh_first; ifp && !result;
	    ifp = ifp->if_link.tqe_next) {
		ifnet_lock_shared(ifp);
		for (ifa = ifp->if_addrhead.tqh_first; ifa;
		    ifa = ifa->ifa_link.tqe_next) {
			IFA_LOCK_SPIN(ifa);
			if (ifa->ifa_addr->sa_family != addr->sa_family) {
				IFA_UNLOCK(ifa);
				continue;
			}
			if (ifa_equal(addr, ifa->ifa_addr)) {
				result = ifa;
				IFA_ADDREF_LOCKED(ifa);	/* for caller */
				IFA_UNLOCK(ifa);
				break;
			}
			if ((ifp->if_flags & IFF_BROADCAST) &&
			    ifa->ifa_broadaddr != NULL &&
			    /* IP6 doesn't have broadcast */
			    ifa->ifa_broadaddr->sa_len != 0 &&
			    ifa_equal(ifa->ifa_broadaddr, addr)) {
				result = ifa;
				IFA_ADDREF_LOCKED(ifa);	/* for caller */
				IFA_UNLOCK(ifa);
				break;
			}
			IFA_UNLOCK(ifa);
		}
		ifnet_lock_done(ifp);
	}

	return (result);
}