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
struct twl4030_usb {int /*<<< orphan*/ * usb3v1; int /*<<< orphan*/ * usb1v5; int /*<<< orphan*/ * usb1v8; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROTECT_KEY ; 
 int /*<<< orphan*/  TWL4030_MODULE_PM_MASTER ; 
 int /*<<< orphan*/  TWL4030_MODULE_PM_RECEIVER ; 
 int /*<<< orphan*/  VUSB1V5_DEV_GRP ; 
 int /*<<< orphan*/  VUSB1V5_TYPE ; 
 int /*<<< orphan*/  VUSB1V8_DEV_GRP ; 
 int /*<<< orphan*/  VUSB1V8_TYPE ; 
 int /*<<< orphan*/  VUSB3V1_DEV_GRP ; 
 int /*<<< orphan*/  VUSB3V1_TYPE ; 
 int /*<<< orphan*/  VUSB_DEDICATED1 ; 
 int /*<<< orphan*/  VUSB_DEDICATED2 ; 
 void* regulator_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twl4030_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_usb_ldo_init(struct twl4030_usb *twl)
{
	/* Enable writing to power configuration registers */
	twl4030_i2c_write_u8(TWL4030_MODULE_PM_MASTER, 0xC0, PROTECT_KEY);
	twl4030_i2c_write_u8(TWL4030_MODULE_PM_MASTER, 0x0C, PROTECT_KEY);

	/* put VUSB3V1 LDO in active state */
	twl4030_i2c_write_u8(TWL4030_MODULE_PM_RECEIVER, 0, VUSB_DEDICATED2);

	/* input to VUSB3V1 LDO is from VBAT, not VBUS */
	twl4030_i2c_write_u8(TWL4030_MODULE_PM_RECEIVER, 0x14, VUSB_DEDICATED1);

	/* Initialize 3.1V regulator */
	twl4030_i2c_write_u8(TWL4030_MODULE_PM_RECEIVER, 0, VUSB3V1_DEV_GRP);

	twl->usb3v1 = regulator_get(twl->dev, "usb3v1");
	if (IS_ERR(twl->usb3v1))
		return -ENODEV;

	twl4030_i2c_write_u8(TWL4030_MODULE_PM_RECEIVER, 0, VUSB3V1_TYPE);

	/* Initialize 1.5V regulator */
	twl4030_i2c_write_u8(TWL4030_MODULE_PM_RECEIVER, 0, VUSB1V5_DEV_GRP);

	twl->usb1v5 = regulator_get(twl->dev, "usb1v5");
	if (IS_ERR(twl->usb1v5))
		goto fail1;

	twl4030_i2c_write_u8(TWL4030_MODULE_PM_RECEIVER, 0, VUSB1V5_TYPE);

	/* Initialize 1.8V regulator */
	twl4030_i2c_write_u8(TWL4030_MODULE_PM_RECEIVER, 0, VUSB1V8_DEV_GRP);

	twl->usb1v8 = regulator_get(twl->dev, "usb1v8");
	if (IS_ERR(twl->usb1v8))
		goto fail2;

	twl4030_i2c_write_u8(TWL4030_MODULE_PM_RECEIVER, 0, VUSB1V8_TYPE);

	/* disable access to power configuration registers */
	twl4030_i2c_write_u8(TWL4030_MODULE_PM_MASTER, 0, PROTECT_KEY);

	return 0;

fail2:
	regulator_put(twl->usb1v5);
	twl->usb1v5 = NULL;
fail1:
	regulator_put(twl->usb3v1);
	twl->usb3v1 = NULL;
	return -ENODEV;
}