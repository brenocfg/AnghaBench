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
struct net_device {int mc_count; int flags; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int dmi_addrlen; struct dev_mc_list* next; int /*<<< orphan*/  dmi_addr; } ;
struct adapter {int devflags_prev; int /*<<< orphan*/  macopts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct adapter*) ; 
 int EINVAL ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MAC_ALLMCAST ; 
 int /*<<< orphan*/  MAC_BCAST ; 
 int /*<<< orphan*/  MAC_DIRECTED ; 
 int /*<<< orphan*/  MAC_MCAST ; 
 int /*<<< orphan*/  MAC_PROMISC ; 
 int STATUS_SUCCESS ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  slic_config_set (struct adapter*,int) ; 
 int slic_mcast_add_list (struct adapter*,char*) ; 
 int /*<<< orphan*/  slic_mcast_set_bit (struct adapter*,char*) ; 
 int /*<<< orphan*/  slic_mcast_set_mask (struct adapter*) ; 

__attribute__((used)) static void slic_mcast_set_list(struct net_device *dev)
{
	struct adapter *adapter = (struct adapter *)netdev_priv(dev);
	int status = STATUS_SUCCESS;
	int i;
	char *addresses;
	struct dev_mc_list *mc_list = dev->mc_list;
	int mc_count = dev->mc_count;

	ASSERT(adapter);

	for (i = 1; i <= mc_count; i++) {
		addresses = (char *) &mc_list->dmi_addr;
		if (mc_list->dmi_addrlen == 6) {
			status = slic_mcast_add_list(adapter, addresses);
			if (status != STATUS_SUCCESS)
				break;
		} else {
			status = -EINVAL;
			break;
		}
		slic_mcast_set_bit(adapter, addresses);
		mc_list = mc_list->next;
	}

	if (adapter->devflags_prev != dev->flags) {
		adapter->macopts = MAC_DIRECTED;
		if (dev->flags) {
			if (dev->flags & IFF_BROADCAST)
				adapter->macopts |= MAC_BCAST;
			if (dev->flags & IFF_PROMISC)
				adapter->macopts |= MAC_PROMISC;
			if (dev->flags & IFF_ALLMULTI)
				adapter->macopts |= MAC_ALLMCAST;
			if (dev->flags & IFF_MULTICAST)
				adapter->macopts |= MAC_MCAST;
		}
		adapter->devflags_prev = dev->flags;
		slic_config_set(adapter, true);
	} else {
		if (status == STATUS_SUCCESS)
			slic_mcast_set_mask(adapter);
	}
	return;
}