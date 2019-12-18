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
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_REG_GPHY_SHADOW ; 
 int MDIO_REG_GPHY_SHADOW_LED_SEL2 ; 
 int MDIO_REG_GPHY_SHADOW_WR_ENA ; 
 int /*<<< orphan*/  MDIO_REG_INTR_MASK ; 
 int MDIO_REG_INTR_MASK_LINK_STATUS ; 
#define  PHY_INIT 128 
 int /*<<< orphan*/  bnx2x_cl22_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_cl22_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_54618se_specific_func(struct bnx2x_phy *phy,
					struct link_params *params,
					u32 action)
{
	struct bnx2x *bp = params->bp;
	u16 temp;
	switch (action) {
	case PHY_INIT:
		/* Configure LED4: set to INTR (0x6). */
		/* Accessing shadow register 0xe. */
		bnx2x_cl22_write(bp, phy,
				 MDIO_REG_GPHY_SHADOW,
				 MDIO_REG_GPHY_SHADOW_LED_SEL2);
		bnx2x_cl22_read(bp, phy,
				MDIO_REG_GPHY_SHADOW,
				&temp);
		temp &= ~(0xf << 4);
		temp |= (0x6 << 4);
		bnx2x_cl22_write(bp, phy,
				 MDIO_REG_GPHY_SHADOW,
				 MDIO_REG_GPHY_SHADOW_WR_ENA | temp);
		/* Configure INTR based on link status change. */
		bnx2x_cl22_write(bp, phy,
				 MDIO_REG_INTR_MASK,
				 ~MDIO_REG_INTR_MASK_LINK_STATUS);
		break;
	}
}