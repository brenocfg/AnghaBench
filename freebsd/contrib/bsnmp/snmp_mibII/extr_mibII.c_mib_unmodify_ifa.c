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
struct mibifa {int /*<<< orphan*/  inbcast; int /*<<< orphan*/  inmask; int /*<<< orphan*/  inaddr; int /*<<< orphan*/  ifindex; } ;
struct mibif {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct mibif* mib_find_if (int /*<<< orphan*/ ) ; 
 int mib_iflist_bad ; 
 scalar_t__ siocaifaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mib_unmodify_ifa(struct mibifa *ifa)
{
	struct mibif *ifp;

	if ((ifp = mib_find_if(ifa->ifindex)) == NULL) {
		/* ups. */
		mib_iflist_bad = 1;
		return;
	}

	if (siocaifaddr(ifp->name, ifa->inaddr, ifa->inmask, ifa->inbcast)) {
		/* ups. */
		mib_iflist_bad = 1;
		return;
	}
}