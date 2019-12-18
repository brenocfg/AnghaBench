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
struct twl4030_usb {int /*<<< orphan*/  usb3v1; int /*<<< orphan*/  usb1v8; int /*<<< orphan*/  usb1v5; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_CLK_CTRL ; 
 int PHY_CLK_CTRL_CLK32K_EN ; 
 int PHY_CLK_CTRL_CLOCKGATING_EN ; 
 int /*<<< orphan*/  PHY_PWR_CTRL ; 
 int PHY_PWR_PHYPWD ; 
 int /*<<< orphan*/  TWL4030_MODULE_PM_RECEIVER ; 
 int /*<<< orphan*/  VUSB_DEDICATED2 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_i2c_write_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int twl4030_usb_read (struct twl4030_usb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_usb_write (struct twl4030_usb*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ twl4030_usb_write_verify (struct twl4030_usb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void twl4030_phy_power(struct twl4030_usb *twl, int on)
{
	u8 pwr;

	pwr = twl4030_usb_read(twl, PHY_PWR_CTRL);
	if (on) {
		regulator_enable(twl->usb3v1);
		regulator_enable(twl->usb1v8);
		/*
		 * Disabling usb3v1 regulator (= writing 0 to VUSB3V1_DEV_GRP
		 * in twl4030) resets the VUSB_DEDICATED2 register. This reset
		 * enables VUSB3V1_SLEEP bit that remaps usb3v1 ACTIVE state to
		 * SLEEP. We work around this by clearing the bit after usv3v1
		 * is re-activated. This ensures that VUSB3V1 is really active.
		 */
		twl4030_i2c_write_u8(TWL4030_MODULE_PM_RECEIVER, 0,
							VUSB_DEDICATED2);
		regulator_enable(twl->usb1v5);
		pwr &= ~PHY_PWR_PHYPWD;
		WARN_ON(twl4030_usb_write_verify(twl, PHY_PWR_CTRL, pwr) < 0);
		twl4030_usb_write(twl, PHY_CLK_CTRL,
				  twl4030_usb_read(twl, PHY_CLK_CTRL) |
					(PHY_CLK_CTRL_CLOCKGATING_EN |
						PHY_CLK_CTRL_CLK32K_EN));
	} else  {
		pwr |= PHY_PWR_PHYPWD;
		WARN_ON(twl4030_usb_write_verify(twl, PHY_PWR_CTRL, pwr) < 0);
		regulator_disable(twl->usb1v5);
		regulator_disable(twl->usb1v8);
		regulator_disable(twl->usb3v1);
	}
}