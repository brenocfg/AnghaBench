#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct slave {int /*<<< orphan*/  dev; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addrlen; int /*<<< orphan*/  dmi_addr; struct dev_mc_list* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;
struct bonding {TYPE_2__* dev; TYPE_1__ params; } ;
struct TYPE_4__ {int flags; struct dev_mc_list* mc_list; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  USES_PRIMARY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_mc_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_mc_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_allmulti (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_set_promiscuity (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bond_mc_swap(struct bonding *bond, struct slave *new_active,
			 struct slave *old_active)
{
	struct dev_mc_list *dmi;

	if (!USES_PRIMARY(bond->params.mode))
		/* nothing to do -  mc list is already up-to-date on
		 * all slaves
		 */
		return;

	if (old_active) {
		if (bond->dev->flags & IFF_PROMISC)
			dev_set_promiscuity(old_active->dev, -1);

		if (bond->dev->flags & IFF_ALLMULTI)
			dev_set_allmulti(old_active->dev, -1);

		for (dmi = bond->dev->mc_list; dmi; dmi = dmi->next)
			dev_mc_delete(old_active->dev, dmi->dmi_addr,
				      dmi->dmi_addrlen, 0);
	}

	if (new_active) {
		/* FIXME: Signal errors upstream. */
		if (bond->dev->flags & IFF_PROMISC)
			dev_set_promiscuity(new_active->dev, 1);

		if (bond->dev->flags & IFF_ALLMULTI)
			dev_set_allmulti(new_active->dev, 1);

		for (dmi = bond->dev->mc_list; dmi; dmi = dmi->next)
			dev_mc_add(new_active->dev, dmi->dmi_addr,
				   dmi->dmi_addrlen, 0);
	}
}