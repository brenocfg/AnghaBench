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
struct cphy {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
#define  AEL2020_GPIO_CFG 132 
#define  AEL2020_GPIO_CTRL 131 
#define  AEL2020_GPIO_LSTAT 130 
#define  AEL2020_GPIO_MODDET 129 
#define  MDIO_MMD_PMAPMD 128 
 int get_link_status_r (struct cphy*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy2portid (struct cphy*) ; 
 int set_phy_regs (struct cphy*,struct reg_val const*) ; 
 int /*<<< orphan*/  t3_link_changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t3_phy_lasi_intr_enable (struct cphy*) ; 

__attribute__((used)) static int ael2020_intr_enable(struct cphy *phy)
{
	static const struct reg_val regs[] = {
		/* output Module's Loss Of Signal (LOS) to LED */
		{ MDIO_MMD_PMAPMD, AEL2020_GPIO_CFG+AEL2020_GPIO_LSTAT,
			0xffff, 0x4 },
		{ MDIO_MMD_PMAPMD, AEL2020_GPIO_CTRL,
			0xffff, 0x8 << (AEL2020_GPIO_LSTAT*4) },

		 /* enable module detect status change interrupts */
		{ MDIO_MMD_PMAPMD, AEL2020_GPIO_CTRL,
			0xffff, 0x2 << (AEL2020_GPIO_MODDET*4) },

		/* end */
		{ 0, 0, 0, 0 }
	};
	int err, link_ok = 0;

	/* set up "link status" LED and enable module change interrupts */
	err = set_phy_regs(phy, regs);
	if (err)
		return err;

	err = get_link_status_r(phy, &link_ok, NULL, NULL, NULL);
	if (err)
		return err;
	if (link_ok)
		t3_link_changed(phy->adapter,
				phy2portid(phy));

	err = t3_phy_lasi_intr_enable(phy);
	if (err)
		return err;

	return 0;
}