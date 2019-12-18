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
struct TYPE_2__ {int phy_id; int phy_id_mask; int supports_gmii; int reg_num_mask; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; struct net_device* dev; } ;
struct octeon_ethernet {TYPE_1__ mii_info; int /*<<< orphan*/  port; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cvm_oct_mdio_dummy_read ; 
 int /*<<< orphan*/  cvm_oct_mdio_dummy_write ; 
 int /*<<< orphan*/  cvm_oct_mdio_read ; 
 int /*<<< orphan*/  cvm_oct_mdio_write ; 
 int cvmx_helper_board_get_mii_address (int /*<<< orphan*/ ) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 

int cvm_oct_mdio_setup_device(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	int phy_id = cvmx_helper_board_get_mii_address(priv->port);
	if (phy_id != -1) {
		priv->mii_info.dev = dev;
		priv->mii_info.phy_id = phy_id;
		priv->mii_info.phy_id_mask = 0xff;
		priv->mii_info.supports_gmii = 1;
		priv->mii_info.reg_num_mask = 0x1f;
		priv->mii_info.mdio_read = cvm_oct_mdio_read;
		priv->mii_info.mdio_write = cvm_oct_mdio_write;
	} else {
		/* Supply dummy MDIO routines so the kernel won't crash
		   if the user tries to read them */
		priv->mii_info.mdio_read = cvm_oct_mdio_dummy_read;
		priv->mii_info.mdio_write = cvm_oct_mdio_dummy_write;
	}
	return 0;
}