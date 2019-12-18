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
struct ovcamchip_window {int quarter; int clockdiv; } ;
struct ovcamchip {int /*<<< orphan*/  mono; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct ovcamchip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  ov_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  ov_write_mask (struct i2c_client*,int,int,int) ; 

__attribute__((used)) static int ov7x20_mode_init(struct i2c_client *c, struct ovcamchip_window *win)
{
	struct ovcamchip *ov = i2c_get_clientdata(c);
	int qvga = win->quarter;

	/******** QVGA-specific regs ********/
	ov_write_mask(c, 0x14, qvga?0x20:0x00, 0x20);
	ov_write_mask(c, 0x28, qvga?0x00:0x20, 0x20);
	ov_write(c, 0x24, qvga?0x20:0x3a);
	ov_write(c, 0x25, qvga?0x30:0x60);
	ov_write_mask(c, 0x2d, qvga?0x40:0x00, 0x40);
	if (!ov->mono)
		ov_write_mask(c, 0x67, qvga?0xf0:0x90, 0xf0);
	ov_write_mask(c, 0x74, qvga?0x20:0x00, 0x20);

	/******** Clock programming ********/

	ov_write(c, 0x11, win->clockdiv);

	return 0;
}