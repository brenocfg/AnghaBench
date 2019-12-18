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
struct reg_val {int member_1; int member_2; int member_3; int /*<<< orphan*/  const member_0; } ;
struct cphy {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
#define  MDIO_MMD_PMAPMD 128 
 int /*<<< orphan*/  edc_sr ; 
 int /*<<< orphan*/  msleep (int) ; 
 int set_phy_regs (struct cphy*,struct reg_val const*) ; 

__attribute__((used)) static int ael2020_setup_sr_edc(struct cphy *phy)
{
	static const struct reg_val regs[] = {
		/* set CDR offset to 10 */
		{ MDIO_MMD_PMAPMD, 0xcc01, 0xffff, 0x488a },

		/* adjust 10G RX bias current */
		{ MDIO_MMD_PMAPMD, 0xcb1b, 0xffff, 0x0200 },
		{ MDIO_MMD_PMAPMD, 0xcb1c, 0xffff, 0x00f0 },
		{ MDIO_MMD_PMAPMD, 0xcc06, 0xffff, 0x00e0 },

		/* end */
		{ 0, 0, 0, 0 }
	};
	int err;

	err = set_phy_regs(phy, regs);
	msleep(50);
	if (err)
		return err;

	phy->priv = edc_sr;
	return 0;
}