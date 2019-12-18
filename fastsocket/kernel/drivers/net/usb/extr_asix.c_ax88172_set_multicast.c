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
typedef  int u8 ;
typedef  int u32 ;
struct usbnet {int /*<<< orphan*/  data; } ;
struct net_device {int flags; scalar_t__ mc_count; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {struct dev_mc_list* next; int /*<<< orphan*/  dmi_addr; } ;
struct asix_data {int* multi_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX_CMD_WRITE_MULTI_FILTER ; 
 int /*<<< orphan*/  AX_CMD_WRITE_RX_CTL ; 
 scalar_t__ AX_MAX_MCAST ; 
 int /*<<< orphan*/  AX_MCAST_FILTER_SIZE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  asix_write_cmd_async (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ether_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ax88172_set_multicast(struct net_device *net)
{
	struct usbnet *dev = netdev_priv(net);
	struct asix_data *data = (struct asix_data *)&dev->data;
	u8 rx_ctl = 0x8c;

	if (net->flags & IFF_PROMISC) {
		rx_ctl |= 0x01;
	} else if (net->flags & IFF_ALLMULTI
		   || net->mc_count > AX_MAX_MCAST) {
		rx_ctl |= 0x02;
	} else if (net->mc_count == 0) {
		/* just broadcast and directed */
	} else {
		/* We use the 20 byte dev->data
		 * for our 8 byte filter buffer
		 * to avoid allocating memory that
		 * is tricky to free later */
		struct dev_mc_list *mc_list = net->mc_list;
		u32 crc_bits;
		int i;

		memset(data->multi_filter, 0, AX_MCAST_FILTER_SIZE);

		/* Build the multicast hash filter. */
		for (i = 0; i < net->mc_count; i++) {
			crc_bits =
			    ether_crc(ETH_ALEN,
				      mc_list->dmi_addr) >> 26;
			data->multi_filter[crc_bits >> 3] |=
			    1 << (crc_bits & 7);
			mc_list = mc_list->next;
		}

		asix_write_cmd_async(dev, AX_CMD_WRITE_MULTI_FILTER, 0, 0,
				   AX_MCAST_FILTER_SIZE, data->multi_filter);

		rx_ctl |= 0x10;
	}

	asix_write_cmd_async(dev, AX_CMD_WRITE_RX_CTL, rx_ctl, 0, 0, NULL);
}