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
struct mibifa {int /*<<< orphan*/  flags; int /*<<< orphan*/  inaddr; int /*<<< orphan*/  ifindex; } ;
struct mibif {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MIBIFA_DESTROYED ; 
 struct mibif* mib_find_if (int /*<<< orphan*/ ) ; 
 int mib_iflist_bad ; 
 scalar_t__ siocdifaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

int
mib_destroy_ifa(struct mibifa *ifa)
{
	struct mibif *ifp;

	if ((ifp = mib_find_if(ifa->ifindex)) == NULL) {
		/* ups. */
		mib_iflist_bad = 1;
		return (-1);
	}
	if (siocdifaddr(ifp->name, ifa->inaddr)) {
		/* ups. */
		syslog(LOG_ERR, "SIOCDIFADDR: %m");
		mib_iflist_bad = 1;
		return (-1);
	}
	ifa->flags |= MIBIFA_DESTROYED;
	return (0);
}