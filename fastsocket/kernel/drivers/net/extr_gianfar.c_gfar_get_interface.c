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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct gfar_private {scalar_t__ interface; int device_flags; TYPE_1__* regs; } ;
typedef  scalar_t__ phy_interface_t ;
struct TYPE_2__ {int /*<<< orphan*/  ecntrl; } ;

/* Variables and functions */
 int ECNTRL_REDUCED_MII_MODE ; 
 int ECNTRL_REDUCED_MODE ; 
 int ECNTRL_SGMII_MODE ; 
 int ECNTRL_TBI_MODE ; 
 int FSL_GIANFAR_DEV_HAS_GIGABIT ; 
 scalar_t__ PHY_INTERFACE_MODE_GMII ; 
 scalar_t__ PHY_INTERFACE_MODE_MII ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 scalar_t__ PHY_INTERFACE_MODE_RMII ; 
 scalar_t__ PHY_INTERFACE_MODE_RTBI ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 scalar_t__ PHY_INTERFACE_MODE_TBI ; 
 int gfar_read (int /*<<< orphan*/ *) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static phy_interface_t gfar_get_interface(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);
	u32 ecntrl = gfar_read(&priv->regs->ecntrl);

	if (ecntrl & ECNTRL_SGMII_MODE)
		return PHY_INTERFACE_MODE_SGMII;

	if (ecntrl & ECNTRL_TBI_MODE) {
		if (ecntrl & ECNTRL_REDUCED_MODE)
			return PHY_INTERFACE_MODE_RTBI;
		else
			return PHY_INTERFACE_MODE_TBI;
	}

	if (ecntrl & ECNTRL_REDUCED_MODE) {
		if (ecntrl & ECNTRL_REDUCED_MII_MODE)
			return PHY_INTERFACE_MODE_RMII;
		else {
			phy_interface_t interface = priv->interface;

			/*
			 * This isn't autodetected right now, so it must
			 * be set by the device tree or platform code.
			 */
			if (interface == PHY_INTERFACE_MODE_RGMII_ID)
				return PHY_INTERFACE_MODE_RGMII_ID;

			return PHY_INTERFACE_MODE_RGMII;
		}
	}

	if (priv->device_flags & FSL_GIANFAR_DEV_HAS_GIGABIT)
		return PHY_INTERFACE_MODE_GMII;

	return PHY_INTERFACE_MODE_MII;
}