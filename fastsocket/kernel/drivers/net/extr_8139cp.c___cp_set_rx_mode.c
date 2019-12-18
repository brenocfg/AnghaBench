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
typedef  int u32 ;
struct net_device {int flags; scalar_t__ mc_count; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addr; struct dev_mc_list* next; } ;
struct cp_private {int rx_config; } ;

/* Variables and functions */
 int AcceptAllPhys ; 
 int AcceptBroadcast ; 
 int AcceptMulticast ; 
 int AcceptMyPhys ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ MAR0 ; 
 scalar_t__ RxConfig ; 
 int cp_rx_config ; 
 int /*<<< orphan*/  cpw32_f (scalar_t__,int) ; 
 int ether_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ multicast_filter_limit ; 
 struct cp_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void __cp_set_rx_mode (struct net_device *dev)
{
	struct cp_private *cp = netdev_priv(dev);
	u32 mc_filter[2];	/* Multicast hash filter */
	int i, rx_mode;

	/* Note: do not reorder, GCC is clever about common statements. */
	if (dev->flags & IFF_PROMISC) {
		/* Unconditionally log net taps. */
		rx_mode =
		    AcceptBroadcast | AcceptMulticast | AcceptMyPhys |
		    AcceptAllPhys;
		mc_filter[1] = mc_filter[0] = 0xffffffff;
	} else if ((dev->mc_count > multicast_filter_limit)
		   || (dev->flags & IFF_ALLMULTI)) {
		/* Too many to filter perfectly -- accept all multicasts. */
		rx_mode = AcceptBroadcast | AcceptMulticast | AcceptMyPhys;
		mc_filter[1] = mc_filter[0] = 0xffffffff;
	} else {
		struct dev_mc_list *mclist;
		rx_mode = AcceptBroadcast | AcceptMyPhys;
		mc_filter[1] = mc_filter[0] = 0;
		for (i = 0, mclist = dev->mc_list; mclist && i < dev->mc_count;
		     i++, mclist = mclist->next) {
			int bit_nr = ether_crc(ETH_ALEN, mclist->dmi_addr) >> 26;

			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
			rx_mode |= AcceptMulticast;
		}
	}

	/* We can safely update without stopping the chip. */
	cp->rx_config = cp_rx_config | rx_mode;
	cpw32_f (RxConfig, cp->rx_config);

	cpw32_f (MAR0 + 0, mc_filter[0]);
	cpw32_f (MAR0 + 4, mc_filter[1]);
}