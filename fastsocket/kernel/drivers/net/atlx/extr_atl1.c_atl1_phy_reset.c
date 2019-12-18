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
typedef  int u32 ;
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct atl1_hw {int media_type; scalar_t__ hw_addr; struct atl1_adapter* back; } ;
struct atl1_adapter {struct pci_dev* pdev; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int MDIO_BUSY ; 
 int MDIO_START ; 
 int MEDIA_TYPE_1000M_FULL ; 
#define  MEDIA_TYPE_100M_FULL 130 
#define  MEDIA_TYPE_100M_HALF 129 
#define  MEDIA_TYPE_10M_FULL 128 
 int MEDIA_TYPE_AUTO_SENSOR ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int MII_CR_AUTO_NEG_EN ; 
 int MII_CR_FULL_DUPLEX ; 
 int MII_CR_RESET ; 
 int MII_CR_SPEED_10 ; 
 int MII_CR_SPEED_100 ; 
 scalar_t__ REG_MDIO_CTRL ; 
 scalar_t__ atl1_write_phy_reg (struct atl1_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ netif_msg_hw (struct atl1_adapter*) ; 

__attribute__((used)) static s32 atl1_phy_reset(struct atl1_hw *hw)
{
	struct pci_dev *pdev = hw->back->pdev;
	struct atl1_adapter *adapter = hw->back;
	s32 ret_val;
	u16 phy_data;

	if (hw->media_type == MEDIA_TYPE_AUTO_SENSOR ||
	    hw->media_type == MEDIA_TYPE_1000M_FULL)
		phy_data = MII_CR_RESET | MII_CR_AUTO_NEG_EN;
	else {
		switch (hw->media_type) {
		case MEDIA_TYPE_100M_FULL:
			phy_data =
			    MII_CR_FULL_DUPLEX | MII_CR_SPEED_100 |
			    MII_CR_RESET;
			break;
		case MEDIA_TYPE_100M_HALF:
			phy_data = MII_CR_SPEED_100 | MII_CR_RESET;
			break;
		case MEDIA_TYPE_10M_FULL:
			phy_data =
			    MII_CR_FULL_DUPLEX | MII_CR_SPEED_10 | MII_CR_RESET;
			break;
		default:
			/* MEDIA_TYPE_10M_HALF: */
			phy_data = MII_CR_SPEED_10 | MII_CR_RESET;
			break;
		}
	}

	ret_val = atl1_write_phy_reg(hw, MII_BMCR, phy_data);
	if (ret_val) {
		u32 val;
		int i;
		/* pcie serdes link may be down! */
		if (netif_msg_hw(adapter))
			dev_dbg(&pdev->dev, "pcie phy link down\n");

		for (i = 0; i < 25; i++) {
			msleep(1);
			val = ioread32(hw->hw_addr + REG_MDIO_CTRL);
			if (!(val & (MDIO_START | MDIO_BUSY)))
				break;
		}

		if ((val & (MDIO_START | MDIO_BUSY)) != 0) {
			if (netif_msg_hw(adapter))
				dev_warn(&pdev->dev,
					"pcie link down at least 25ms\n");
			return ret_val;
		}
	}
	return 0;
}