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
struct i2c_msg {int addr; unsigned char* buf; int len; scalar_t__ flags; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 unsigned char CTRL_C10 ; 
 unsigned char CTRL_CKSW ; 
 unsigned char CTRL_CPSW ; 
 int ENODEV ; 
 int MAIN_MLED4 ; 
 int MAIN_MSW ; 
 struct i2c_adapter* i2c_get_adapter (int /*<<< orphan*/ ) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static int kfr2r09_lcd_backlight(int on)
{
	struct i2c_adapter *a;
	struct i2c_msg msg;
	unsigned char buf[2];
	int ret;

	a = i2c_get_adapter(0);
	if (!a)
		return -ENODEV;

	buf[0] = 0x00;
	if (on)
		buf[1] = CTRL_CPSW | CTRL_C10 | CTRL_CKSW;
	else
		buf[1] = 0;

	msg.addr = 0x75;
	msg.buf = buf;
	msg.len = 2;
	msg.flags = 0;
	ret = i2c_transfer(a, &msg, 1);
	if (ret != 1)
		return -ENODEV;

	buf[0] = 0x01;
	if (on)
		buf[1] = MAIN_MSW | MAIN_MLED4 | 0x0c;
	else
		buf[1] = 0;

	msg.addr = 0x75;
	msg.buf = buf;
	msg.len = 2;
	msg.flags = 0;
	ret = i2c_transfer(a, &msg, 1);
	if (ret != 1)
		return -ENODEV;

	return 0;
}