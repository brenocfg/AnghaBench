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
struct mibifa {int /*<<< orphan*/  inaddr; int /*<<< orphan*/  ifindex; } ;
struct mibif {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_ifa (struct mibifa*) ; 
 struct mibif* mib_find_if (int /*<<< orphan*/ ) ; 
 int mib_iflist_bad ; 
 scalar_t__ siocdifaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mib_uncreate_ifa(struct mibifa *ifa)
{
	struct mibif *ifp;

	if ((ifp = mib_find_if(ifa->ifindex)) == NULL) {
		/* ups. */
		mib_iflist_bad = 1;
		return;
	}
	if (siocdifaddr(ifp->name, ifa->inaddr)) {
		/* ups. */
		mib_iflist_bad = 1;
		return;
	}

	destroy_ifa(ifa);
}