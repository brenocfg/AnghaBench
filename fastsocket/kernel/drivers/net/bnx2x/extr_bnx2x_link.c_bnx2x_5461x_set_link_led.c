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
typedef  int u8 ;
typedef  int u16 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
#define  LED_MODE_FRONT_PANEL_OFF 131 
#define  LED_MODE_OFF 130 
#define  LED_MODE_ON 129 
#define  LED_MODE_OPER 128 
 int /*<<< orphan*/  MDIO_REG_GPHY_SHADOW ; 
 int MDIO_REG_GPHY_SHADOW_LED_SEL1 ; 
 int MDIO_REG_GPHY_SHADOW_WR_ENA ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_cl22_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_cl22_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_5461x_set_link_led(struct bnx2x_phy *phy,
				       struct link_params *params, u8 mode)
{
	struct bnx2x *bp = params->bp;
	u16 temp;

	bnx2x_cl22_write(bp, phy,
		MDIO_REG_GPHY_SHADOW,
		MDIO_REG_GPHY_SHADOW_LED_SEL1);
	bnx2x_cl22_read(bp, phy,
		MDIO_REG_GPHY_SHADOW,
		&temp);
	temp &= 0xff00;

	DP(NETIF_MSG_LINK, "54618x set link led (mode=%x)\n", mode);
	switch (mode) {
	case LED_MODE_FRONT_PANEL_OFF:
	case LED_MODE_OFF:
		temp |= 0x00ee;
		break;
	case LED_MODE_OPER:
		temp |= 0x0001;
		break;
	case LED_MODE_ON:
		temp |= 0x00ff;
		break;
	default:
		break;
	}
	bnx2x_cl22_write(bp, phy,
		MDIO_REG_GPHY_SHADOW,
		MDIO_REG_GPHY_SHADOW_WR_ENA | temp);
	return;
}