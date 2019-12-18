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
struct net_device {int mtu; } ;
struct nes_vnic {int nic_index; scalar_t__ max_frame_size; struct nes_device* nesdev; } ;
struct nes_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_ZLEN ; 
 int /*<<< orphan*/  NES_IDX_NIC_MULTICAST_ALL ; 
 int /*<<< orphan*/  NES_IDX_NIC_UNICAST_ALL ; 
 scalar_t__ VLAN_ETH_HLEN ; 
 int max_mtu ; 
 int /*<<< orphan*/  nes_netdev_open (struct net_device*) ; 
 int /*<<< orphan*/  nes_netdev_stop (struct net_device*) ; 
 int /*<<< orphan*/  nes_nic_init_timer_defaults (struct nes_device*,int) ; 
 int nes_read_indexed (struct nes_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_write_indexed (struct nes_device*,int /*<<< orphan*/ ,int) ; 
 struct nes_vnic* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int nes_netdev_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct nes_vnic	*nesvnic = netdev_priv(netdev);
	struct nes_device *nesdev = nesvnic->nesdev;
	int ret = 0;
	u8 jumbomode = 0;
	u32 nic_active;
	u32 nic_active_bit;
	u32 uc_all_active;
	u32 mc_all_active;

	if ((new_mtu < ETH_ZLEN) || (new_mtu > max_mtu))
		return -EINVAL;

	netdev->mtu = new_mtu;
	nesvnic->max_frame_size	= new_mtu + VLAN_ETH_HLEN;

	if (netdev->mtu	> 1500)	{
		jumbomode=1;
	}
	nes_nic_init_timer_defaults(nesdev, jumbomode);

	if (netif_running(netdev)) {
		nic_active_bit = 1 << nesvnic->nic_index;
		mc_all_active = nes_read_indexed(nesdev,
				NES_IDX_NIC_MULTICAST_ALL) & nic_active_bit;
		uc_all_active = nes_read_indexed(nesdev,
				NES_IDX_NIC_UNICAST_ALL)  & nic_active_bit;

		nes_netdev_stop(netdev);
		nes_netdev_open(netdev);

		nic_active = nes_read_indexed(nesdev,
					NES_IDX_NIC_MULTICAST_ALL);
		nic_active |= mc_all_active;
		nes_write_indexed(nesdev, NES_IDX_NIC_MULTICAST_ALL,
							nic_active);

		nic_active = nes_read_indexed(nesdev, NES_IDX_NIC_UNICAST_ALL);
		nic_active |= uc_all_active;
		nes_write_indexed(nesdev, NES_IDX_NIC_UNICAST_ALL, nic_active);
	}

	return ret;
}