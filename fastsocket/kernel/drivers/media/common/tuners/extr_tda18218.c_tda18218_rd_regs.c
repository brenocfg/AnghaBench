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
typedef  size_t u8 ;
struct tda18218_priv {int /*<<< orphan*/  i2c; TYPE_1__* cfg; } ;
struct i2c_msg {int len; char* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_address; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,size_t) ; 
 int /*<<< orphan*/  warn (char*,int,size_t,size_t) ; 

__attribute__((used)) static int tda18218_rd_regs(struct tda18218_priv *priv, u8 reg, u8 *val, u8 len)
{
	int ret;
	u8 buf[reg+len]; /* we must start read always from reg 0x00 */
	struct i2c_msg msg[2] = {
		{
			.addr = priv->cfg->i2c_address,
			.flags = 0,
			.len = 1,
			.buf = "\x00",
		}, {
			.addr = priv->cfg->i2c_address,
			.flags = I2C_M_RD,
			.len = sizeof(buf),
			.buf = buf,
		}
	};

	ret = i2c_transfer(priv->i2c, msg, 2);
	if (ret == 2) {
		memcpy(val, &buf[reg], len);
		ret = 0;
	} else {
		warn("i2c rd failed ret:%d reg:%02x len:%d", ret, reg, len);
		ret = -EREMOTEIO;
	}

	return ret;
}