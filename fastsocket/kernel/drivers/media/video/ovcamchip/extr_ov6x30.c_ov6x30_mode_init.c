#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ovcamchip_window {scalar_t__ format; int /*<<< orphan*/  clockdiv; scalar_t__ quarter; } ;
struct i2c_client {TYPE_1__* adapter; } ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ I2C_HW_SMBUS_OV518 ; 
 scalar_t__ VIDEO_PALETTE_GREY ; 
 int /*<<< orphan*/  ov_write (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov_write_mask (struct i2c_client*,int,int,int) ; 

__attribute__((used)) static int ov6x30_mode_init(struct i2c_client *c, struct ovcamchip_window *win)
{
	/******** QCIF-specific regs ********/

	ov_write_mask(c, 0x14, win->quarter?0x20:0x00, 0x20);

	/******** Palette-specific regs ********/

	if (win->format == VIDEO_PALETTE_GREY) {
		if (c->adapter->id == I2C_HW_SMBUS_OV518) {
			/* Do nothing - we're already in 8-bit mode */
		} else {
			ov_write_mask(c, 0x13, 0x20, 0x20);
		}
	} else {
		/* The OV518 needs special treatment. Although both the OV518
		 * and the OV6630 support a 16-bit video bus, only the 8 bit Y
		 * bus is actually used. The UV bus is tied to ground.
		 * Therefore, the OV6630 needs to be in 8-bit multiplexed
		 * output mode */

		if (c->adapter->id == I2C_HW_SMBUS_OV518) {
			/* Do nothing - we want to stay in 8-bit mode */
			/* Warning: Messing with reg 0x13 breaks OV518 color */
		} else {
			ov_write_mask(c, 0x13, 0x00, 0x20);
		}
	}

	/******** Clock programming ********/

	ov_write(c, 0x11, win->clockdiv);

	return 0;
}