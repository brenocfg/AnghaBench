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
struct net_device {int flags; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addrlen; int /*<<< orphan*/  dmi_addr; struct dev_mc_list* next; } ;
struct bonding {int flags; int /*<<< orphan*/  lock; struct dev_mc_list* mc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  bond_mc_add (struct bonding*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_mc_delete (struct bonding*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_mc_list_copy (struct dev_mc_list*,struct bonding*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_mc_list_destroy (struct bonding*) ; 
 int /*<<< orphan*/  bond_mc_list_find_dmi (struct dev_mc_list*,struct dev_mc_list*) ; 
 int /*<<< orphan*/  bond_set_allmulti (struct bonding*,int) ; 
 int /*<<< orphan*/  bond_set_promiscuity (struct bonding*,int) ; 
 struct bonding* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bond_set_multicast_list(struct net_device *bond_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);
	struct dev_mc_list *dmi;

	/*
	 * Do promisc before checking multicast_mode
	 */
	if ((bond_dev->flags & IFF_PROMISC) && !(bond->flags & IFF_PROMISC))
		/*
		 * FIXME: Need to handle the error when one of the multi-slaves
		 * encounters error.
		 */
		bond_set_promiscuity(bond, 1);


	if (!(bond_dev->flags & IFF_PROMISC) && (bond->flags & IFF_PROMISC))
		bond_set_promiscuity(bond, -1);


	/* set allmulti flag to slaves */
	if ((bond_dev->flags & IFF_ALLMULTI) && !(bond->flags & IFF_ALLMULTI))
		/*
		 * FIXME: Need to handle the error when one of the multi-slaves
		 * encounters error.
		 */
		bond_set_allmulti(bond, 1);


	if (!(bond_dev->flags & IFF_ALLMULTI) && (bond->flags & IFF_ALLMULTI))
		bond_set_allmulti(bond, -1);


	read_lock(&bond->lock);

	bond->flags = bond_dev->flags;

	/* looking for addresses to add to slaves' mc list */
	for (dmi = bond_dev->mc_list; dmi; dmi = dmi->next) {
		if (!bond_mc_list_find_dmi(dmi, bond->mc_list))
			bond_mc_add(bond, dmi->dmi_addr, dmi->dmi_addrlen);
	}

	/* looking for addresses to delete from slaves' list */
	for (dmi = bond->mc_list; dmi; dmi = dmi->next) {
		if (!bond_mc_list_find_dmi(dmi, bond_dev->mc_list))
			bond_mc_delete(bond, dmi->dmi_addr, dmi->dmi_addrlen);
	}

	/* save master's multicast list */
	bond_mc_list_destroy(bond);
	bond_mc_list_copy(bond_dev->mc_list, bond, GFP_ATOMIC);

	read_unlock(&bond->lock);
}