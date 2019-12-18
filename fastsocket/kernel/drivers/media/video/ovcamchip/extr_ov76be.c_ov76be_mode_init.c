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
struct ovcamchip_window {int quarter; scalar_t__ format; int clockdiv; int width; int height; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ VIDEO_PALETTE_GREY ; 
 int /*<<< orphan*/  ov_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  ov_write_mask (struct i2c_client*,int,int,int) ; 

__attribute__((used)) static int ov76be_mode_init(struct i2c_client *c, struct ovcamchip_window *win)
{
	int qvga = win->quarter;

	/******** QVGA-specific regs ********/

	ov_write(c, 0x14, qvga?0xa4:0x84);

	/******** Palette-specific regs ********/

	if (win->format == VIDEO_PALETTE_GREY) {
		ov_write_mask(c, 0x0e, 0x40, 0x40);
		ov_write_mask(c, 0x13, 0x20, 0x20);
	} else {
		ov_write_mask(c, 0x0e, 0x00, 0x40);
		ov_write_mask(c, 0x13, 0x00, 0x20);
	}

	/******** Clock programming ********/

	ov_write(c, 0x11, win->clockdiv);

	/******** Resolution-specific ********/

	if (win->width == 640 && win->height == 480)
		ov_write(c, 0x35, 0x9e);
	else
		ov_write(c, 0x35, 0x1e);

	return 0;
}