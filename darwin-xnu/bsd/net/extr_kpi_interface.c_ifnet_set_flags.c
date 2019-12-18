#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int u_int16_t ;
typedef  TYPE_1__* ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_10__ {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int IFF_MULTICAST ; 
 int IFF_UP ; 
 int /*<<< orphan*/ * IGMP_IFINFO (TYPE_1__*) ; 
 int /*<<< orphan*/ * MLD_IFINFO (TYPE_1__*) ; 
 int /*<<< orphan*/  if_updown (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ifnet_lock_done (TYPE_1__*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (TYPE_1__*) ; 
 int /*<<< orphan*/  igmp_initsilent (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mld6_initsilent (TYPE_1__*,int /*<<< orphan*/ *) ; 

errno_t
ifnet_set_flags(ifnet_t interface, u_int16_t new_flags, u_int16_t mask)
{
	uint16_t old_flags;

	if (interface == NULL)
		return (EINVAL);

	ifnet_lock_exclusive(interface);

	/* If we are modifying the up/down state, call if_updown */
	if ((mask & IFF_UP) != 0) {
		if_updown(interface, (new_flags & IFF_UP) == IFF_UP);
	}

	old_flags = interface->if_flags;
	interface->if_flags = (new_flags & mask) | (interface->if_flags & ~mask);
	/* If we are modifying the multicast flag, set/unset the silent flag */
	if ((old_flags & IFF_MULTICAST) !=
	    (interface->if_flags & IFF_MULTICAST)) {
#if INET
		if (IGMP_IFINFO(interface) != NULL)
			igmp_initsilent(interface, IGMP_IFINFO(interface));
#endif /* INET */
#if INET6
		if (MLD_IFINFO(interface) != NULL)
			mld6_initsilent(interface, MLD_IFINFO(interface));
#endif /* INET6 */
	}

	ifnet_lock_done(interface);

	return (0);
}