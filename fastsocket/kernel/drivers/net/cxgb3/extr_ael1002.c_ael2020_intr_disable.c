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
struct reg_val {int member_2; int member_3; int /*<<< orphan*/  const member_1; int /*<<< orphan*/  const member_0; } ;
struct cphy {int dummy; } ;

/* Variables and functions */
#define  AEL2020_GPIO_CTRL 131 
#define  AEL2020_GPIO_LSTAT 130 
#define  AEL2020_GPIO_MODDET 129 
#define  MDIO_MMD_PMAPMD 128 
 int set_phy_regs (struct cphy*,struct reg_val const*) ; 
 int t3_phy_lasi_intr_disable (struct cphy*) ; 

__attribute__((used)) static int ael2020_intr_disable(struct cphy *phy)
{
	static const struct reg_val regs[] = {
		/* reset "link status" LED to "off" */
		{ MDIO_MMD_PMAPMD, AEL2020_GPIO_CTRL,
			0xffff, 0xb << (AEL2020_GPIO_LSTAT*4) },

		/* disable module detect status change interrupts */
		{ MDIO_MMD_PMAPMD, AEL2020_GPIO_CTRL,
			0xffff, 0x1 << (AEL2020_GPIO_MODDET*4) },

		/* end */
		{ 0, 0, 0, 0 }
	};
	int err;

	/* turn off "link status" LED and disable module change interrupts */
	err = set_phy_regs(phy, regs);
	if (err)
		return err;

	return t3_phy_lasi_intr_disable(phy);
}