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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED1000 ; 
 int CTL1000_AS_MASTER ; 
 int CTL1000_ENABLE_MASTER ; 
 int EBUSY ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_TG3_DSP_ADDRESS ; 
 int /*<<< orphan*/  MII_TG3_DSP_CONTROL ; 
 int /*<<< orphan*/  MII_TG3_EXT_CTRL ; 
 int tg3_bmcr_reset (struct tg3*) ; 
 int tg3_phy_reset_chanpat (struct tg3*) ; 
 int tg3_phy_toggle_auxctl_smdsp (struct tg3*,int) ; 
 int tg3_phy_write_and_check_testpat (struct tg3*,int*) ; 
 int /*<<< orphan*/  tg3_phydsp_write (struct tg3*,int,int) ; 
 scalar_t__ tg3_readphy (struct tg3*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tg3_writephy (struct tg3*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tg3_phy_reset_5703_4_5(struct tg3 *tp)
{
	u32 reg32, phy9_orig;
	int retries, do_phy_reset, err;

	retries = 10;
	do_phy_reset = 1;
	do {
		if (do_phy_reset) {
			err = tg3_bmcr_reset(tp);
			if (err)
				return err;
			do_phy_reset = 0;
		}

		/* Disable transmitter and interrupt.  */
		if (tg3_readphy(tp, MII_TG3_EXT_CTRL, &reg32))
			continue;

		reg32 |= 0x3000;
		tg3_writephy(tp, MII_TG3_EXT_CTRL, reg32);

		/* Set full-duplex, 1000 mbps.  */
		tg3_writephy(tp, MII_BMCR,
			     BMCR_FULLDPLX | BMCR_SPEED1000);

		/* Set to master mode.  */
		if (tg3_readphy(tp, MII_CTRL1000, &phy9_orig))
			continue;

		tg3_writephy(tp, MII_CTRL1000,
			     CTL1000_AS_MASTER | CTL1000_ENABLE_MASTER);

		err = tg3_phy_toggle_auxctl_smdsp(tp, true);
		if (err)
			return err;

		/* Block the PHY control access.  */
		tg3_phydsp_write(tp, 0x8005, 0x0800);

		err = tg3_phy_write_and_check_testpat(tp, &do_phy_reset);
		if (!err)
			break;
	} while (--retries);

	err = tg3_phy_reset_chanpat(tp);
	if (err)
		return err;

	tg3_phydsp_write(tp, 0x8005, 0x0000);

	tg3_writephy(tp, MII_TG3_DSP_ADDRESS, 0x8200);
	tg3_writephy(tp, MII_TG3_DSP_CONTROL, 0x0000);

	tg3_phy_toggle_auxctl_smdsp(tp, false);

	tg3_writephy(tp, MII_CTRL1000, phy9_orig);

	if (!tg3_readphy(tp, MII_TG3_EXT_CTRL, &reg32)) {
		reg32 &= ~0x3000;
		tg3_writephy(tp, MII_TG3_EXT_CTRL, reg32);
	} else if (!err)
		err = -EBUSY;

	return err;
}