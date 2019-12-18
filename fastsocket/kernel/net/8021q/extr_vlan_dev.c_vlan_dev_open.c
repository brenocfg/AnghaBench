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
struct vlan_dev_info {int flags; int /*<<< orphan*/  real_dev_addr; struct net_device* real_dev; } ;
struct net_device {int flags; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int VLAN_FLAG_GVRP ; 
 scalar_t__ compare_ether_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dev_set_allmulti (struct net_device*,int) ; 
 int dev_set_promiscuity (struct net_device*,int) ; 
 int dev_unicast_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_unicast_delete (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 struct vlan_dev_info* vlan_dev_info (struct net_device*) ; 
 int /*<<< orphan*/  vlan_gvrp_request_join (struct net_device*) ; 

__attribute__((used)) static int vlan_dev_open(struct net_device *dev)
{
	struct vlan_dev_info *vlan = vlan_dev_info(dev);
	struct net_device *real_dev = vlan->real_dev;
	int err;

	if (!(real_dev->flags & IFF_UP))
		return -ENETDOWN;

	if (compare_ether_addr(dev->dev_addr, real_dev->dev_addr)) {
		err = dev_unicast_add(real_dev, dev->dev_addr);
		if (err < 0)
			goto out;
	}

	if (dev->flags & IFF_ALLMULTI) {
		err = dev_set_allmulti(real_dev, 1);
		if (err < 0)
			goto del_unicast;
	}
	if (dev->flags & IFF_PROMISC) {
		err = dev_set_promiscuity(real_dev, 1);
		if (err < 0)
			goto clear_allmulti;
	}

	memcpy(vlan->real_dev_addr, real_dev->dev_addr, ETH_ALEN);

	if (vlan->flags & VLAN_FLAG_GVRP)
		vlan_gvrp_request_join(dev);

	if (netif_carrier_ok(real_dev))
		netif_carrier_on(dev);
	return 0;

clear_allmulti:
	if (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(real_dev, -1);
del_unicast:
	if (compare_ether_addr(dev->dev_addr, real_dev->dev_addr))
		dev_unicast_delete(real_dev, dev->dev_addr);
out:
	netif_carrier_off(dev);
	return err;
}