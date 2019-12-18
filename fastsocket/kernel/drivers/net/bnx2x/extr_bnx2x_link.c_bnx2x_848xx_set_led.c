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
typedef  int u16 ;
struct bnx2x_reg_set {int member_1; int member_2; int val; int /*<<< orphan*/  reg; int /*<<< orphan*/  const devad; int /*<<< orphan*/  const member_0; } ;
struct bnx2x_phy {scalar_t__ type; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bnx2x_reg_set*) ; 
#define  MDIO_AN_DEVAD 135 
#define  MDIO_PMA_DEVAD 134 
#define  MDIO_PMA_REG_8481_LED1_MASK 133 
#define  MDIO_PMA_REG_8481_LED2_MASK 132 
#define  MDIO_PMA_REG_8481_LED3_BLINK 131 
#define  MDIO_PMA_REG_8481_LED3_MASK 130 
 int /*<<< orphan*/  MDIO_PMA_REG_8481_LINK_SIGNAL ; 
#define  MDIO_PMA_REG_84823_BLINK_RATE_VAL_15P9HZ 129 
 int MDIO_PMA_REG_84823_CTL_LED_CTL_1 ; 
#define  MDIO_PMA_REG_84823_CTL_SLOW_CLK_CNT_HIGH 128 
 int /*<<< orphan*/  MDIO_PMA_REG_84823_LED3_STRETCH_EN ; 
 int MDIO_PMA_REG_84833_CTL_LED_CTL_1 ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833 ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834 ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_read_or_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/  const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_848xx_set_led(struct bnx2x *bp,
				struct bnx2x_phy *phy)
{
	u16 val, offset, i;
	static struct bnx2x_reg_set reg_set[] = {
		{MDIO_PMA_DEVAD, MDIO_PMA_REG_8481_LED1_MASK, 0x0080},
		{MDIO_PMA_DEVAD, MDIO_PMA_REG_8481_LED2_MASK, 0x0018},
		{MDIO_PMA_DEVAD, MDIO_PMA_REG_8481_LED3_MASK, 0x0006},
		{MDIO_PMA_DEVAD, MDIO_PMA_REG_8481_LED3_BLINK, 0x0000},
		{MDIO_PMA_DEVAD, MDIO_PMA_REG_84823_CTL_SLOW_CLK_CNT_HIGH,
			MDIO_PMA_REG_84823_BLINK_RATE_VAL_15P9HZ},
		{MDIO_AN_DEVAD, 0xFFFB, 0xFFFD}
	};
	/* PHYC_CTL_LED_CTL */
	bnx2x_cl45_read(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8481_LINK_SIGNAL, &val);
	val &= 0xFE00;
	val |= 0x0092;

	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_8481_LINK_SIGNAL, val);

	for (i = 0; i < ARRAY_SIZE(reg_set); i++)
		bnx2x_cl45_write(bp, phy, reg_set[i].devad, reg_set[i].reg,
				 reg_set[i].val);

	if ((phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833) ||
	    (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834))
		offset = MDIO_PMA_REG_84833_CTL_LED_CTL_1;
	else
		offset = MDIO_PMA_REG_84823_CTL_LED_CTL_1;

	/* stretch_en for LED3*/
	bnx2x_cl45_read_or_write(bp, phy,
				 MDIO_PMA_DEVAD, offset,
				 MDIO_PMA_REG_84823_LED3_STRETCH_EN);
}