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
struct mibifa {int /*<<< orphan*/  flags; int /*<<< orphan*/  inbcast; int /*<<< orphan*/  inmask; int /*<<< orphan*/  inaddr; int /*<<< orphan*/  ifindex; } ;
struct mibif {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIBIFA_DESTROYED ; 
 struct mibif* mib_find_if (int /*<<< orphan*/ ) ; 
 scalar_t__ siocaifaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mib_undestroy_ifa(struct mibifa *ifa)
{
	struct mibif *ifp;

	if ((ifp = mib_find_if(ifa->ifindex)) == NULL)
		/* keep it destroyed */
		return;

	if (siocaifaddr(ifp->name, ifa->inaddr, ifa->inmask, ifa->inbcast))
		/* keep it destroyed */
		return;

	ifa->flags &= ~MIBIFA_DESTROYED;
}