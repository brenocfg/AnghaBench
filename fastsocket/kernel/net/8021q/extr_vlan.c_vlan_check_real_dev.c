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
typedef  int /*<<< orphan*/  u16 ;
struct net_device_ops {int /*<<< orphan*/  ndo_vlan_rx_kill_vid; int /*<<< orphan*/  ndo_vlan_rx_add_vid; int /*<<< orphan*/  ndo_vlan_rx_register; } ;
struct net_device {char* name; int features; struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 int EEXIST ; 
 int EOPNOTSUPP ; 
 int NETIF_F_HW_VLAN_FILTER ; 
 int NETIF_F_HW_VLAN_RX ; 
 int NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/ * __find_vlan_dev (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 

int vlan_check_real_dev(struct net_device *real_dev, u16 vlan_id)
{
	const char *name = real_dev->name;
	const struct net_device_ops *ops = real_dev->netdev_ops;

	if (real_dev->features & NETIF_F_VLAN_CHALLENGED) {
		pr_info("8021q: VLANs not supported on %s\n", name);
		return -EOPNOTSUPP;
	}

	if ((real_dev->features & NETIF_F_HW_VLAN_RX) && !ops->ndo_vlan_rx_register) {
		pr_info("8021q: device %s has buggy VLAN hw accel\n", name);
		return -EOPNOTSUPP;
	}

	if ((real_dev->features & NETIF_F_HW_VLAN_FILTER) &&
	    (!ops->ndo_vlan_rx_add_vid || !ops->ndo_vlan_rx_kill_vid)) {
		pr_info("8021q: Device %s has buggy VLAN hw accel\n", name);
		return -EOPNOTSUPP;
	}

	if (__find_vlan_dev(real_dev, vlan_id) != NULL)
		return -EEXIST;

	return 0;
}