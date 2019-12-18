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
struct bnx2x_phy {int flags; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int FLAGS_NOC ; 
#define  LED_MODE_FRONT_PANEL_OFF 131 
#define  LED_MODE_OFF 130 
#define  LED_MODE_ON 129 
#define  LED_MODE_OPER 128 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8727_GPIO_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8727_PCS_OPT_CTRL ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_8727_set_link_led(struct bnx2x_phy *phy,
				    struct link_params *params, u8 mode)
{
	struct bnx2x *bp = params->bp;
	u16 led_mode_bitmask = 0;
	u16 gpio_pins_bitmask = 0;
	u16 val;
	/* Only NOC flavor requires to set the LED specifically */
	if (!(phy->flags & FLAGS_NOC))
		return;
	switch (mode) {
	case LED_MODE_FRONT_PANEL_OFF:
	case LED_MODE_OFF:
		led_mode_bitmask = 0;
		gpio_pins_bitmask = 0x03;
		break;
	case LED_MODE_ON:
		led_mode_bitmask = 0;
		gpio_pins_bitmask = 0x02;
		break;
	case LED_MODE_OPER:
		led_mode_bitmask = 0x60;
		gpio_pins_bitmask = 0x11;
		break;
	}
	bnx2x_cl45_read(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8727_PCS_OPT_CTRL,
			&val);
	val &= 0xff8f;
	val |= led_mode_bitmask;
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_8727_PCS_OPT_CTRL,
			 val);
	bnx2x_cl45_read(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8727_GPIO_CTRL,
			&val);
	val &= 0xffe0;
	val |= gpio_pins_bitmask;
	bnx2x_cl45_write(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_8727_GPIO_CTRL,
			 val);
}