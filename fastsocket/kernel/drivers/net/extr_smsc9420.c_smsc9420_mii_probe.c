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
struct smsc9420_pdata {int last_duplex; int last_carrier; struct phy_device* phy_dev; TYPE_1__* mii_bus; } ;
struct phy_device {int supported; int advertising; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; TYPE_2__* drv; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  addr; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct phy_device** phy_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct phy_device*) ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int PHY_BASIC_FEATURES ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  PROBE ; 
 int PTR_ERR (struct phy_device*) ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Pause ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 struct phy_device* phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_phy_adjust_link ; 
 int /*<<< orphan*/  smsc_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smsc9420_mii_probe(struct net_device *dev)
{
	struct smsc9420_pdata *pd = netdev_priv(dev);
	struct phy_device *phydev = NULL;

	BUG_ON(pd->phy_dev);

	/* Device only supports internal PHY at address 1 */
	if (!pd->mii_bus->phy_map[1]) {
		pr_err("%s: no PHY found at address 1\n", dev->name);
		return -ENODEV;
	}

	phydev = pd->mii_bus->phy_map[1];
	smsc_info(PROBE, "PHY addr %d, phy_id 0x%08X", phydev->addr,
		phydev->phy_id);

	phydev = phy_connect(dev, dev_name(&phydev->dev),
		&smsc9420_phy_adjust_link, 0, PHY_INTERFACE_MODE_MII);

	if (IS_ERR(phydev)) {
		pr_err("%s: Could not attach to PHY\n", dev->name);
		return PTR_ERR(phydev);
	}

	pr_info("%s: attached PHY driver [%s] (mii_bus:phy_addr=%s, irq=%d)\n",
		dev->name, phydev->drv->name, dev_name(&phydev->dev), phydev->irq);

	/* mask with MAC supported features */
	phydev->supported &= (PHY_BASIC_FEATURES | SUPPORTED_Pause |
			      SUPPORTED_Asym_Pause);
	phydev->advertising = phydev->supported;

	pd->phy_dev = phydev;
	pd->last_duplex = -1;
	pd->last_carrier = -1;

	return 0;
}