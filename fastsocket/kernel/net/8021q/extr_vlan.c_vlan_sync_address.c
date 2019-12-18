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
struct vlan_dev_info {int /*<<< orphan*/  real_dev_addr; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ compare_ether_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_unicast_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_unicast_delete (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vlan_dev_info* vlan_dev_info (struct net_device*) ; 

__attribute__((used)) static void vlan_sync_address(struct net_device *dev,
			      struct net_device *vlandev)
{
	struct vlan_dev_info *vlan = vlan_dev_info(vlandev);

	/* May be called without an actual change */
	if (!compare_ether_addr(vlan->real_dev_addr, dev->dev_addr))
		return;

	/* vlan address was different from the old address and is equal to
	 * the new address */
	if (compare_ether_addr(vlandev->dev_addr, vlan->real_dev_addr) &&
	    !compare_ether_addr(vlandev->dev_addr, dev->dev_addr))
		dev_unicast_delete(dev, vlandev->dev_addr);

	/* vlan address was equal to the old address and is different from
	 * the new address */
	if (!compare_ether_addr(vlandev->dev_addr, vlan->real_dev_addr) &&
	    compare_ether_addr(vlandev->dev_addr, dev->dev_addr))
		dev_unicast_add(dev, vlandev->dev_addr);

	memcpy(vlan->real_dev_addr, dev->dev_addr, ETH_ALEN);
}