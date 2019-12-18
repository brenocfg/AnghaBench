#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct gfar_private {int device_flags; int oldduplex; TYPE_1__* phydev; int /*<<< orphan*/  phy_node; scalar_t__ oldspeed; scalar_t__ oldlink; } ;
typedef  scalar_t__ phy_interface_t ;
struct TYPE_3__ {int supported; int advertising; } ;

/* Variables and functions */
 int ENODEV ; 
 int FSL_GIANFAR_DEV_HAS_GIGABIT ; 
 int GFAR_SUPPORTED ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int SUPPORTED_1000baseT_Full ; 
 int /*<<< orphan*/  adjust_link ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gfar_configure_serdes (struct net_device*) ; 
 scalar_t__ gfar_get_interface (struct net_device*) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 TYPE_1__* of_phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* of_phy_connect_fixed_link (struct net_device*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int init_phy(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);
	uint gigabit_support =
		priv->device_flags & FSL_GIANFAR_DEV_HAS_GIGABIT ?
		SUPPORTED_1000baseT_Full : 0;
	phy_interface_t interface;

	priv->oldlink = 0;
	priv->oldspeed = 0;
	priv->oldduplex = -1;

	interface = gfar_get_interface(dev);

	priv->phydev = of_phy_connect(dev, priv->phy_node, &adjust_link, 0,
				      interface);
	if (!priv->phydev)
		priv->phydev = of_phy_connect_fixed_link(dev, &adjust_link,
							 interface);
	if (!priv->phydev) {
		dev_err(&dev->dev, "could not attach to PHY\n");
		return -ENODEV;
	}

	if (interface == PHY_INTERFACE_MODE_SGMII)
		gfar_configure_serdes(dev);

	/* Remove any features not supported by the controller */
	priv->phydev->supported &= (GFAR_SUPPORTED | gigabit_support);
	priv->phydev->advertising = priv->phydev->supported;

	return 0;
}