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
typedef  int u32 ;
struct tg3 {TYPE_1__* mdio_bus; } ;
struct phy_device {scalar_t__ interface; TYPE_2__* drv; } ;
struct TYPE_4__ {int phy_id; int phy_id_mask; } ;
struct TYPE_3__ {struct phy_device** phy_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_EXT_RGMII_MODE ; 
 int /*<<< orphan*/  MAC_PHYCFG1 ; 
 int MAC_PHYCFG1_RGMII_EXT_RX_DEC ; 
 int MAC_PHYCFG1_RGMII_INT ; 
 int MAC_PHYCFG1_RGMII_SND_STAT_EN ; 
 int MAC_PHYCFG1_RXCLK_TIMEOUT ; 
 int MAC_PHYCFG1_RXCLK_TO_MASK ; 
 int MAC_PHYCFG1_TXCLK_TIMEOUT ; 
 int MAC_PHYCFG1_TXCLK_TO_MASK ; 
 int MAC_PHYCFG1_TXC_DRV ; 
 int /*<<< orphan*/  MAC_PHYCFG2 ; 
 int MAC_PHYCFG2_50610_LED_MODES ; 
 int MAC_PHYCFG2_AC131_LED_MODES ; 
 int MAC_PHYCFG2_ACT_MASK_MASK ; 
 int MAC_PHYCFG2_EMODE_MASK_MASK ; 
 int MAC_PHYCFG2_FMODE_MASK_MASK ; 
 int MAC_PHYCFG2_GMODE_MASK_MASK ; 
 int MAC_PHYCFG2_INBAND_ENABLE ; 
 int MAC_PHYCFG2_QUAL_MASK_MASK ; 
 int MAC_PHYCFG2_RTL8201E_LED_MODES ; 
 int MAC_PHYCFG2_RTL8211C_LED_MODES ; 
 int MAC_RGMII_MODE_RX_ACTIVITY ; 
 int MAC_RGMII_MODE_RX_ENG_DET ; 
 int MAC_RGMII_MODE_RX_INT_B ; 
 int MAC_RGMII_MODE_RX_QUALITY ; 
 int MAC_RGMII_MODE_TX_ENABLE ; 
 int MAC_RGMII_MODE_TX_LOWPWR ; 
 int MAC_RGMII_MODE_TX_RESET ; 
#define  PHY_ID_BCM50610 132 
#define  PHY_ID_BCM50610M 131 
#define  PHY_ID_BCMAC131 130 
#define  PHY_ID_RTL8201E 129 
#define  PHY_ID_RTL8211C 128 
 scalar_t__ PHY_INTERFACE_MODE_RGMII ; 
 int /*<<< orphan*/  RGMII_EXT_IBND_RX_EN ; 
 int /*<<< orphan*/  RGMII_EXT_IBND_TX_EN ; 
 int /*<<< orphan*/  RGMII_INBAND_DISABLE ; 
 size_t TG3_PHY_MII_ADDR ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tg3_mdio_config_5785(struct tg3 *tp)
{
	u32 val;
	struct phy_device *phydev;

	phydev = tp->mdio_bus->phy_map[TG3_PHY_MII_ADDR];
	switch (phydev->drv->phy_id & phydev->drv->phy_id_mask) {
	case PHY_ID_BCM50610:
	case PHY_ID_BCM50610M:
		val = MAC_PHYCFG2_50610_LED_MODES;
		break;
	case PHY_ID_BCMAC131:
		val = MAC_PHYCFG2_AC131_LED_MODES;
		break;
	case PHY_ID_RTL8211C:
		val = MAC_PHYCFG2_RTL8211C_LED_MODES;
		break;
	case PHY_ID_RTL8201E:
		val = MAC_PHYCFG2_RTL8201E_LED_MODES;
		break;
	default:
		return;
	}

	if (phydev->interface != PHY_INTERFACE_MODE_RGMII) {
		tw32(MAC_PHYCFG2, val);

		val = tr32(MAC_PHYCFG1);
		val &= ~(MAC_PHYCFG1_RGMII_INT |
			 MAC_PHYCFG1_RXCLK_TO_MASK | MAC_PHYCFG1_TXCLK_TO_MASK);
		val |= MAC_PHYCFG1_RXCLK_TIMEOUT | MAC_PHYCFG1_TXCLK_TIMEOUT;
		tw32(MAC_PHYCFG1, val);

		return;
	}

	if (!tg3_flag(tp, RGMII_INBAND_DISABLE))
		val |= MAC_PHYCFG2_EMODE_MASK_MASK |
		       MAC_PHYCFG2_FMODE_MASK_MASK |
		       MAC_PHYCFG2_GMODE_MASK_MASK |
		       MAC_PHYCFG2_ACT_MASK_MASK   |
		       MAC_PHYCFG2_QUAL_MASK_MASK |
		       MAC_PHYCFG2_INBAND_ENABLE;

	tw32(MAC_PHYCFG2, val);

	val = tr32(MAC_PHYCFG1);
	val &= ~(MAC_PHYCFG1_RXCLK_TO_MASK | MAC_PHYCFG1_TXCLK_TO_MASK |
		 MAC_PHYCFG1_RGMII_EXT_RX_DEC | MAC_PHYCFG1_RGMII_SND_STAT_EN);
	if (!tg3_flag(tp, RGMII_INBAND_DISABLE)) {
		if (tg3_flag(tp, RGMII_EXT_IBND_RX_EN))
			val |= MAC_PHYCFG1_RGMII_EXT_RX_DEC;
		if (tg3_flag(tp, RGMII_EXT_IBND_TX_EN))
			val |= MAC_PHYCFG1_RGMII_SND_STAT_EN;
	}
	val |= MAC_PHYCFG1_RXCLK_TIMEOUT | MAC_PHYCFG1_TXCLK_TIMEOUT |
	       MAC_PHYCFG1_RGMII_INT | MAC_PHYCFG1_TXC_DRV;
	tw32(MAC_PHYCFG1, val);

	val = tr32(MAC_EXT_RGMII_MODE);
	val &= ~(MAC_RGMII_MODE_RX_INT_B |
		 MAC_RGMII_MODE_RX_QUALITY |
		 MAC_RGMII_MODE_RX_ACTIVITY |
		 MAC_RGMII_MODE_RX_ENG_DET |
		 MAC_RGMII_MODE_TX_ENABLE |
		 MAC_RGMII_MODE_TX_LOWPWR |
		 MAC_RGMII_MODE_TX_RESET);
	if (!tg3_flag(tp, RGMII_INBAND_DISABLE)) {
		if (tg3_flag(tp, RGMII_EXT_IBND_RX_EN))
			val |= MAC_RGMII_MODE_RX_INT_B |
			       MAC_RGMII_MODE_RX_QUALITY |
			       MAC_RGMII_MODE_RX_ACTIVITY |
			       MAC_RGMII_MODE_RX_ENG_DET;
		if (tg3_flag(tp, RGMII_EXT_IBND_TX_EN))
			val |= MAC_RGMII_MODE_TX_ENABLE |
			       MAC_RGMII_MODE_TX_LOWPWR |
			       MAC_RGMII_MODE_TX_RESET;
	}
	tw32(MAC_EXT_RGMII_MODE, val);
}