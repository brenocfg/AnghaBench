#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device* parent; } ;
struct net_device {int priv_flags; TYPE_1__ dev; } ;
struct neighbour {struct net_device* dev; } ;
struct device {int /*<<< orphan*/ * driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int IFF_802_1Q_VLAN ; 
 TYPE_2__ cxgb4_driver ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device const*) ; 
 int /*<<< orphan*/  t4_l2t_update (int /*<<< orphan*/ ,struct neighbour*) ; 
 struct net_device* vlan_dev_real_dev (struct net_device const*) ; 

__attribute__((used)) static void check_neigh_update(struct neighbour *neigh)
{
	const struct device *parent;
	const struct net_device *netdev = neigh->dev;

	if (netdev->priv_flags & IFF_802_1Q_VLAN)
		netdev = vlan_dev_real_dev(netdev);
	parent = netdev->dev.parent;
	if (parent && parent->driver == &cxgb4_driver.driver)
		t4_l2t_update(dev_get_drvdata(parent), neigh);
}