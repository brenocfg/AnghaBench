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
struct ifnet {int /*<<< orphan*/  if_eflags; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFEF_IPV6_DISABLED ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (struct ifnet*) ; 

int
nd6_if_disable(struct ifnet *ifp, boolean_t enable)
{
	ifnet_lock_shared(ifp);
	if (enable)
		ifp->if_eflags |= IFEF_IPV6_DISABLED;
	else
		ifp->if_eflags &= ~IFEF_IPV6_DISABLED;
	ifnet_lock_done(ifp);

	return (0);
}