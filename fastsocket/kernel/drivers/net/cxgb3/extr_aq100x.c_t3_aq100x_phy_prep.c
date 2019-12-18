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
struct mdio_ops {int dummy; } ;
struct cphy {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_FW_VERSION ; 
 unsigned int AQ_LOWPOWER ; 
 unsigned int AQ_RESET ; 
 int /*<<< orphan*/  AQ_XAUI_RX_CFG ; 
 int /*<<< orphan*/  AQ_XAUI_TX_CFG ; 
 int /*<<< orphan*/  A_T3DBG_GPIO_EN ; 
 int /*<<< orphan*/  CH_WARN (struct adapter*,char*,int,...) ; 
 unsigned int F_GPIO10_OUT_VAL ; 
 unsigned int F_GPIO6_OUT_VAL ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  aq100x_ops ; 
 int /*<<< orphan*/  cphy_init (struct cphy*,struct adapter*,int,int /*<<< orphan*/ *,struct mdio_ops const*,int,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int t3_mdio_change_bits (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int t3_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

int t3_aq100x_phy_prep(struct cphy *phy, struct adapter *adapter, int phy_addr,
		       const struct mdio_ops *mdio_ops)
{
	unsigned int v, v2, gpio, wait;
	int err;

	cphy_init(phy, adapter, phy_addr, &aq100x_ops, mdio_ops,
		  SUPPORTED_1000baseT_Full | SUPPORTED_10000baseT_Full |
		  SUPPORTED_TP | SUPPORTED_Autoneg | SUPPORTED_AUI,
		  "1000/10GBASE-T");

	/*
	 * The PHY has been out of reset ever since the system powered up.  So
	 * we do a hard reset over here.
	 */
	gpio = phy_addr ? F_GPIO10_OUT_VAL : F_GPIO6_OUT_VAL;
	t3_set_reg_field(adapter, A_T3DBG_GPIO_EN, gpio, 0);
	msleep(1);
	t3_set_reg_field(adapter, A_T3DBG_GPIO_EN, gpio, gpio);

	/*
	 * Give it enough time to load the firmware and get ready for mdio.
	 */
	msleep(1000);
	wait = 500; /* in 10ms increments */
	do {
		err = t3_mdio_read(phy, MDIO_MMD_VEND1, MDIO_CTRL1, &v);
		if (err || v == 0xffff) {

			/* Allow prep_adapter to succeed when ffff is read */

			CH_WARN(adapter, "PHY%d: reset failed (0x%x, 0x%x).\n",
				phy_addr, err, v);
			goto done;
		}

		v &= AQ_RESET;
		if (v)
			msleep(10);
	} while (v && --wait);
	if (v) {
		CH_WARN(adapter, "PHY%d: reset timed out (0x%x).\n",
			phy_addr, v);

		goto done; /* let prep_adapter succeed */
	}

	/* Datasheet says 3s max but this has been observed */
	wait = (500 - wait) * 10 + 1000;
	if (wait > 3000)
		CH_WARN(adapter, "PHY%d: reset took %ums\n", phy_addr, wait);

	/* Firmware version check. */
	t3_mdio_read(phy, MDIO_MMD_VEND1, AQ_FW_VERSION, &v);
	if (v != 101)
		CH_WARN(adapter, "PHY%d: unsupported firmware %d\n",
			phy_addr, v);

	/*
	 * The PHY should start in really-low-power mode.  Prepare it for normal
	 * operations.
	 */
	err = t3_mdio_read(phy, MDIO_MMD_VEND1, MDIO_CTRL1, &v);
	if (err)
		return err;
	if (v & AQ_LOWPOWER) {
		err = t3_mdio_change_bits(phy, MDIO_MMD_VEND1, MDIO_CTRL1,
					  AQ_LOWPOWER, 0);
		if (err)
			return err;
		msleep(10);
	} else
		CH_WARN(adapter, "PHY%d does not start in low power mode.\n",
			phy_addr);

	/*
	 * Verify XAUI settings, but let prep succeed no matter what.
	 */
	v = v2 = 0;
	t3_mdio_read(phy, MDIO_MMD_PHYXS, AQ_XAUI_RX_CFG, &v);
	t3_mdio_read(phy, MDIO_MMD_PHYXS, AQ_XAUI_TX_CFG, &v2);
	if (v != 0x1b || v2 != 0x1b)
		CH_WARN(adapter,
			"PHY%d: incorrect XAUI settings (0x%x, 0x%x).\n",
			phy_addr, v, v2);

done:
	return err;
}