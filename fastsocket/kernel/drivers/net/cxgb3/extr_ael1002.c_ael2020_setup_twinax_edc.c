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
typedef  int /*<<< orphan*/  u16 ;
struct reg_val {int member_1; int member_2; int member_3; int /*<<< orphan*/  const member_0; } ;
struct cphy {scalar_t__ priv; int /*<<< orphan*/ * phy_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDC_TWX_AEL2020 ; 
 int EDC_TWX_AEL2020_SIZE ; 
#define  MDIO_MMD_PMAPMD 128 
 scalar_t__ edc_twinax ; 
 int /*<<< orphan*/  msleep (int) ; 
 int set_phy_regs (struct cphy*,struct reg_val const*) ; 
 int t3_get_edc_fw (struct cphy*,int /*<<< orphan*/ ,int) ; 
 int t3_mdio_write (struct cphy*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ael2020_setup_twinax_edc(struct cphy *phy, int modtype)
{
	/* set uC to 40MHz */
	static const struct reg_val uCclock40MHz[] = {
		{ MDIO_MMD_PMAPMD, 0xff28, 0xffff, 0x4001 },
		{ MDIO_MMD_PMAPMD, 0xff2a, 0xffff, 0x0002 },
		{ 0, 0, 0, 0 }
	};

	/* activate uC clock */
	static const struct reg_val uCclockActivate[] = {
		{ MDIO_MMD_PMAPMD, 0xd000, 0xffff, 0x5200 },
		{ 0, 0, 0, 0 }
	};

	/* set PC to start of SRAM and activate uC */
	static const struct reg_val uCactivate[] = {
		{ MDIO_MMD_PMAPMD, 0xd080, 0xffff, 0x0100 },
		{ MDIO_MMD_PMAPMD, 0xd092, 0xffff, 0x0000 },
		{ 0, 0, 0, 0 }
	};
	int i, err;

	/* set uC clock and activate it */
	err = set_phy_regs(phy, uCclock40MHz);
	msleep(500);
	if (err)
		return err;
	err = set_phy_regs(phy, uCclockActivate);
	msleep(500);
	if (err)
		return err;

	if (phy->priv != edc_twinax)
		err = t3_get_edc_fw(phy, EDC_TWX_AEL2020,
				    EDC_TWX_AEL2020_SIZE);
	if (err)
		return err;

	for (i = 0; i <  EDC_TWX_AEL2020_SIZE / sizeof(u16) && !err; i += 2)
		err = t3_mdio_write(phy, MDIO_MMD_PMAPMD,
				    phy->phy_cache[i],
				    phy->phy_cache[i + 1]);
	/* activate uC */
	err = set_phy_regs(phy, uCactivate);
	if (!err)
		phy->priv = edc_twinax;
	return err;
}