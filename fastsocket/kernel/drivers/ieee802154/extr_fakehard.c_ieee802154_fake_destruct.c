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
struct wpan_phy {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct wpan_phy* net_to_phy (struct net_device*) ; 
 int /*<<< orphan*/  wpan_phy_free (struct wpan_phy*) ; 
 int /*<<< orphan*/  wpan_phy_unregister (struct wpan_phy*) ; 

__attribute__((used)) static void ieee802154_fake_destruct(struct net_device *dev)
{
	struct wpan_phy *phy = net_to_phy(dev);

	wpan_phy_unregister(phy);
	free_netdev(dev);
	wpan_phy_free(phy);
}