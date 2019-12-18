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
typedef  size_t uint32_t ;
struct net_device {int flags; int mc_count; struct dev_mc_list* mc_list; } ;
struct et131x_adapter {size_t PacketFilter; int MCAddressCount; int /*<<< orphan*/  Lock; int /*<<< orphan*/ * MCList; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addr; } ;

/* Variables and functions */
 size_t ET131X_PACKET_TYPE_ALL_MULTICAST ; 
 size_t ET131X_PACKET_TYPE_MULTICAST ; 
 size_t ET131X_PACKET_TYPE_PROMISCUOUS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int NIC_MAX_MCAST_LIST ; 
 int /*<<< orphan*/  et131x_set_packet_filter (struct et131x_adapter*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void et131x_multicast(struct net_device *netdev)
{
	struct et131x_adapter *adapter = netdev_priv(netdev);
	uint32_t PacketFilter = 0;
	uint32_t count;
	unsigned long flags;
	struct dev_mc_list *mclist = netdev->mc_list;

	spin_lock_irqsave(&adapter->Lock, flags);

	/* Before we modify the platform-independent filter flags, store them
	 * locally. This allows us to determine if anything's changed and if
	 * we even need to bother the hardware
	 */
	PacketFilter = adapter->PacketFilter;

	/* Clear the 'multicast' flag locally; becuase we only have a single
	 * flag to check multicast, and multiple multicast addresses can be
	 * set, this is the easiest way to determine if more than one
	 * multicast address is being set.
	 */
	PacketFilter &= ~ET131X_PACKET_TYPE_MULTICAST;

	/* Check the net_device flags and set the device independent flags
	 * accordingly
	 */

	if (netdev->flags & IFF_PROMISC) {
		adapter->PacketFilter |= ET131X_PACKET_TYPE_PROMISCUOUS;
	} else {
		adapter->PacketFilter &= ~ET131X_PACKET_TYPE_PROMISCUOUS;
	}

	if (netdev->flags & IFF_ALLMULTI) {
		adapter->PacketFilter |= ET131X_PACKET_TYPE_ALL_MULTICAST;
	}

	if (netdev->mc_count > NIC_MAX_MCAST_LIST) {
		adapter->PacketFilter |= ET131X_PACKET_TYPE_ALL_MULTICAST;
	}

	if (netdev->mc_count < 1) {
		adapter->PacketFilter &= ~ET131X_PACKET_TYPE_ALL_MULTICAST;
		adapter->PacketFilter &= ~ET131X_PACKET_TYPE_MULTICAST;
	} else {
		adapter->PacketFilter |= ET131X_PACKET_TYPE_MULTICAST;
	}

	/* Set values in the private adapter struct */
	adapter->MCAddressCount = netdev->mc_count;

	if (netdev->mc_count) {
		count = netdev->mc_count - 1;
		memcpy(adapter->MCList[count], mclist->dmi_addr, ETH_ALEN);
	}

	/* Are the new flags different from the previous ones? If not, then no
	 * action is required
	 *
	 * NOTE - This block will always update the MCList with the hardware,
	 *        even if the addresses aren't the same.
	 */
	if (PacketFilter != adapter->PacketFilter) {
		/* Call the device's filter function */
		et131x_set_packet_filter(adapter);
	}
	spin_unlock_irqrestore(&adapter->Lock, flags);
}