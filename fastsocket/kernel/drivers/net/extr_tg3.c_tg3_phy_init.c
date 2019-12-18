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
struct tg3 {int phy_flags; TYPE_2__* mdio_bus; TYPE_1__* pdev; int /*<<< orphan*/  dev; } ;
struct phy_device {int interface; int supported; int advertising; int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct phy_device** phy_map; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int PHY_BASIC_FEATURES ; 
 int PHY_GBIT_FEATURES ; 
#define  PHY_INTERFACE_MODE_GMII 130 
#define  PHY_INTERFACE_MODE_MII 129 
#define  PHY_INTERFACE_MODE_RGMII 128 
 int PTR_ERR (struct phy_device*) ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Pause ; 
 int TG3_PHYFLG_10_100_ONLY ; 
 int TG3_PHYFLG_IS_CONNECTED ; 
 size_t TG3_PHY_MII_ADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct phy_device* phy_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int /*<<< orphan*/  tg3_adjust_link ; 
 int /*<<< orphan*/  tg3_bmcr_reset (struct tg3*) ; 

__attribute__((used)) static int tg3_phy_init(struct tg3 *tp)
{
	struct phy_device *phydev;

	if (tp->phy_flags & TG3_PHYFLG_IS_CONNECTED)
		return 0;

	/* Bring the PHY back to a known state. */
	tg3_bmcr_reset(tp);

	phydev = tp->mdio_bus->phy_map[TG3_PHY_MII_ADDR];

	/* Attach the MAC to the PHY. */
	phydev = phy_connect(tp->dev, dev_name(&phydev->dev), tg3_adjust_link,
			     phydev->dev_flags, phydev->interface);
	if (IS_ERR(phydev)) {
		dev_err(&tp->pdev->dev, "Could not attach to PHY\n");
		return PTR_ERR(phydev);
	}

	/* Mask with MAC supported features. */
	switch (phydev->interface) {
	case PHY_INTERFACE_MODE_GMII:
	case PHY_INTERFACE_MODE_RGMII:
		if (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) {
			phydev->supported &= (PHY_GBIT_FEATURES |
					      SUPPORTED_Pause |
					      SUPPORTED_Asym_Pause);
			break;
		}
		/* fallthru */
	case PHY_INTERFACE_MODE_MII:
		phydev->supported &= (PHY_BASIC_FEATURES |
				      SUPPORTED_Pause |
				      SUPPORTED_Asym_Pause);
		break;
	default:
		phy_disconnect(tp->mdio_bus->phy_map[TG3_PHY_MII_ADDR]);
		return -EINVAL;
	}

	tp->phy_flags |= TG3_PHYFLG_IS_CONNECTED;

	phydev->advertising = phydev->supported;

	return 0;
}