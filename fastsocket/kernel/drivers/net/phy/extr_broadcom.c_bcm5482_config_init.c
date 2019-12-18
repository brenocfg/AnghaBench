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
struct phy_device {int dev_flags; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  BCM5482_SHD_LEDS1 ; 
 int BCM5482_SHD_LEDS1_LED1 (int /*<<< orphan*/ ) ; 
 int BCM5482_SHD_LEDS1_LED3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM5482_SHD_MODE ; 
 int BCM5482_SHD_MODE_1000BX ; 
 int /*<<< orphan*/  BCM5482_SHD_SSD ; 
 int BCM5482_SHD_SSD_EN ; 
 int BCM5482_SHD_SSD_LEDM ; 
 int BCM5482_SSD_1000BX_CTL ; 
 int BCM5482_SSD_1000BX_CTL_PWRDOWN ; 
 int BCM5482_SSD_SGMII_SLAVE ; 
 int BCM5482_SSD_SGMII_SLAVE_AD ; 
 int BCM5482_SSD_SGMII_SLAVE_EN ; 
 int /*<<< orphan*/  BCM_LED_SRC_ACTIVITYLED ; 
 int /*<<< orphan*/  BCM_LED_SRC_LINKSPD2 ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int MII_BCM54XX_EXP_SEL_SSD ; 
 int PHY_BCM_FLAGS_MODE_1000BX ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int bcm54xx_config_init (struct phy_device*) ; 
 int bcm54xx_exp_read (struct phy_device*,int) ; 
 int bcm54xx_exp_write (struct phy_device*,int,int) ; 
 int bcm54xx_shadow_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm54xx_shadow_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm5482_config_init(struct phy_device *phydev)
{
	int err, reg;

	err = bcm54xx_config_init(phydev);

	if (phydev->dev_flags & PHY_BCM_FLAGS_MODE_1000BX) {
		/*
		 * Enable secondary SerDes and its use as an LED source
		 */
		reg = bcm54xx_shadow_read(phydev, BCM5482_SHD_SSD);
		bcm54xx_shadow_write(phydev, BCM5482_SHD_SSD,
				     reg |
				     BCM5482_SHD_SSD_LEDM |
				     BCM5482_SHD_SSD_EN);

		/*
		 * Enable SGMII slave mode and auto-detection
		 */
		reg = BCM5482_SSD_SGMII_SLAVE | MII_BCM54XX_EXP_SEL_SSD;
		err = bcm54xx_exp_read(phydev, reg);
		if (err < 0)
			return err;
		err = bcm54xx_exp_write(phydev, reg, err |
					BCM5482_SSD_SGMII_SLAVE_EN |
					BCM5482_SSD_SGMII_SLAVE_AD);
		if (err < 0)
			return err;

		/*
		 * Disable secondary SerDes powerdown
		 */
		reg = BCM5482_SSD_1000BX_CTL | MII_BCM54XX_EXP_SEL_SSD;
		err = bcm54xx_exp_read(phydev, reg);
		if (err < 0)
			return err;
		err = bcm54xx_exp_write(phydev, reg,
					err & ~BCM5482_SSD_1000BX_CTL_PWRDOWN);
		if (err < 0)
			return err;

		/*
		 * Select 1000BASE-X register set (primary SerDes)
		 */
		reg = bcm54xx_shadow_read(phydev, BCM5482_SHD_MODE);
		bcm54xx_shadow_write(phydev, BCM5482_SHD_MODE,
				     reg | BCM5482_SHD_MODE_1000BX);

		/*
		 * LED1=ACTIVITYLED, LED3=LINKSPD[2]
		 * (Use LED1 as secondary SerDes ACTIVITY LED)
		 */
		bcm54xx_shadow_write(phydev, BCM5482_SHD_LEDS1,
			BCM5482_SHD_LEDS1_LED1(BCM_LED_SRC_ACTIVITYLED) |
			BCM5482_SHD_LEDS1_LED3(BCM_LED_SRC_LINKSPD2));

		/*
		 * Auto-negotiation doesn't seem to work quite right
		 * in this mode, so we disable it and force it to the
		 * right speed/duplex setting.  Only 'link status'
		 * is important.
		 */
		phydev->autoneg = AUTONEG_DISABLE;
		phydev->speed = SPEED_1000;
		phydev->duplex = DUPLEX_FULL;
	}

	return err;
}