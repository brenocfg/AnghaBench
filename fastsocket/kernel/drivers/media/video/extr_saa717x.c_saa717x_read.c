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
struct v4l2_subdev {int dummy; } ;
struct i2c_msg {int len; unsigned char* buf; int /*<<< orphan*/  addr; scalar_t__ flags; } ;
struct i2c_client {int /*<<< orphan*/  addr; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ I2C_M_RD ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static u32 saa717x_read(struct v4l2_subdev *sd, u32 reg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct i2c_adapter *adap = client->adapter;
	int fw_addr = (reg >= 0x404 && reg <= 0x4b8) || reg == 0x528;
	unsigned char mm1[2];
	unsigned char mm2[4] = { 0, 0, 0, 0 };
	struct i2c_msg msgs[2];
	u32 value;

	msgs[0].flags = 0;
	msgs[1].flags = I2C_M_RD;
	msgs[0].addr = msgs[1].addr = client->addr;
	mm1[0] = (reg >> 8) & 0xff;
	mm1[1] = reg & 0xff;
	msgs[0].len = 2;
	msgs[0].buf = mm1;
	msgs[1].len = fw_addr ? 3 : 1; /* Multibyte Registers contains *only* 3 bytes */
	msgs[1].buf = mm2;
	i2c_transfer(adap, msgs, 2);

	if (fw_addr)
		value = (mm2[2] & 0xff)  | ((mm2[1] & 0xff) >> 8) | ((mm2[0] & 0xff) >> 16);
	else
		value = mm2[0] & 0xff;

	v4l2_dbg(2, debug, sd, "read:  reg 0x%03x=0x%08x\n", reg, value);
	return value;
}