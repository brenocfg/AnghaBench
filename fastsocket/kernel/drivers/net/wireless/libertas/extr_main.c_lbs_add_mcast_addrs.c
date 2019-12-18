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
struct net_device {int flags; int /*<<< orphan*/  name; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addr; struct dev_mc_list* next; } ;
struct cmd_ds_mac_multicast_adr {int /*<<< orphan*/ * maclist; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IFF_MULTICAST ; 
 int IFF_UP ; 
 int MRVDRV_MAX_MULTICAST_LIST_SIZE ; 
 int /*<<< orphan*/  lbs_deb_net (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mac_in_list (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (struct net_device*) ; 

__attribute__((used)) static int lbs_add_mcast_addrs(struct cmd_ds_mac_multicast_adr *cmd,
			       struct net_device *dev, int nr_addrs)
{
	int i = nr_addrs;
	struct dev_mc_list *mc_list;

	if ((dev->flags & (IFF_UP|IFF_MULTICAST)) != (IFF_UP|IFF_MULTICAST))
		return nr_addrs;

	netif_addr_lock_bh(dev);
	for (mc_list = dev->mc_list; mc_list; mc_list = mc_list->next) {
		if (mac_in_list(cmd->maclist, nr_addrs, mc_list->dmi_addr)) {
			lbs_deb_net("mcast address %s:%pM skipped\n", dev->name,
				    mc_list->dmi_addr);
			continue;
		}

		if (i == MRVDRV_MAX_MULTICAST_LIST_SIZE)
			break;
		memcpy(&cmd->maclist[6*i], mc_list->dmi_addr, ETH_ALEN);
		lbs_deb_net("mcast address %s:%pM added to filter\n", dev->name,
			    mc_list->dmi_addr);
		i++;
	}
	netif_addr_unlock_bh(dev);
	if (mc_list)
		return -EOVERFLOW;

	return i;
}