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
struct phy_device {int addr; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct ethoc {int phy_id; struct phy_device* phy; TYPE_1__* mdio; } ;
struct TYPE_2__ {struct phy_device** phy_map; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_GMII ; 
 int PHY_MAX_ADDR ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ethoc_mdio_poll ; 
 struct ethoc* netdev_priv (struct net_device*) ; 
 struct phy_device* phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ethoc_mdio_probe(struct net_device *dev)
{
	struct ethoc *priv = netdev_priv(dev);
	struct phy_device *phy;
	int i;

	for (i = 0; i < PHY_MAX_ADDR; i++) {
		phy = priv->mdio->phy_map[i];
		if (phy) {
			if (priv->phy_id != -1) {
				/* attach to specified PHY */
				if (priv->phy_id == phy->addr)
					break;
			} else {
				/* autoselect PHY if none was specified */
				if (phy->addr != 0)
					break;
			}
		}
	}

	if (!phy) {
		dev_err(&dev->dev, "no PHY found\n");
		return -ENXIO;
	}

	phy = phy_connect(dev, dev_name(&phy->dev), &ethoc_mdio_poll, 0,
			PHY_INTERFACE_MODE_GMII);
	if (IS_ERR(phy)) {
		dev_err(&dev->dev, "could not attach to PHY\n");
		return PTR_ERR(phy);
	}

	priv->phy = phy;
	return 0;
}