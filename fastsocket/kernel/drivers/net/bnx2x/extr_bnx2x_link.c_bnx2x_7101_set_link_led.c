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
#define  LED_MODE_FRONT_PANEL_OFF 131 
#define  LED_MODE_OFF 130 
#define  LED_MODE_ON 129 
#define  LED_MODE_OPER 128 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_7107_LINK_LED_CNTL ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_7101_set_link_led(struct bnx2x_phy *phy,
				    struct link_params *params, u8 mode)
{
	u16 val = 0;
	struct bnx2x *bp = params->bp;
	switch (mode) {
	case LED_MODE_FRONT_PANEL_OFF:
	case LED_MODE_OFF:
		val = 2;
		break;
	case LED_MODE_ON:
		val = 1;
		break;
	case LED_MODE_OPER:
		val = 0;
		break;
	}
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_7107_LINK_LED_CNTL,
			 val);
}