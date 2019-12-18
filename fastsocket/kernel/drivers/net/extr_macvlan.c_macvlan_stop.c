#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int flags; int /*<<< orphan*/  dev_addr; } ;
struct macvlan_dev {TYPE_1__* port; struct net_device* lowerdev; } ;
struct TYPE_2__ {scalar_t__ passthru; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int /*<<< orphan*/  dev_mc_unsync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  dev_set_allmulti (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_set_promiscuity (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_unicast_delete (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macvlan_hash_del (struct macvlan_dev*) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int macvlan_stop(struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct net_device *lowerdev = vlan->lowerdev;

	dev_mc_unsync(lowerdev, dev);
	if (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(lowerdev, -1);

	if (vlan->port->passthru) {
		dev_set_promiscuity(lowerdev, -1);
		goto hash_del;
	}

	dev_unicast_delete(lowerdev, dev->dev_addr);

hash_del:
	macvlan_hash_del(vlan);
	return 0;
}