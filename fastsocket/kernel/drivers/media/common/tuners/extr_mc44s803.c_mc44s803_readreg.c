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
typedef  int u8 ;
typedef  int u32 ;
struct mc44s803_priv {int /*<<< orphan*/  i2c; TYPE_1__* cfg; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_address; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  MC44S803_ADDR ; 
 int /*<<< orphan*/  MC44S803_D ; 
 int MC44S803_REG_DATAREG ; 
 int MC44S803_REG_SM (int,int /*<<< orphan*/ ) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int mc44s803_writereg (struct mc44s803_priv*,int) ; 
 int /*<<< orphan*/  mc_printk (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mc44s803_readreg(struct mc44s803_priv *priv, u8 reg, u32 *val)
{
	u32 wval;
	u8 buf[3];
	int ret;
	struct i2c_msg msg[] = {
		{ .addr = priv->cfg->i2c_address, .flags = I2C_M_RD,
		  .buf = buf, .len = 3 },
	};

	wval = MC44S803_REG_SM(MC44S803_REG_DATAREG, MC44S803_ADDR) |
	       MC44S803_REG_SM(reg, MC44S803_D);

	ret = mc44s803_writereg(priv, wval);
	if (ret)
		return ret;

	if (i2c_transfer(priv->i2c, msg, 1) != 1) {
		mc_printk(KERN_WARNING, "I2C read failed\n");
		return -EREMOTEIO;
	}

	*val = (buf[0] << 16) | (buf[1] << 8) | buf[2];

	return 0;
}