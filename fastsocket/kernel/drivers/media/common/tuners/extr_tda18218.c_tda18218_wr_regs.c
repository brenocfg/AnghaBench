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
struct tda18218_priv {int /*<<< orphan*/  i2c; TYPE_1__* cfg; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int i2c_wr_max; int /*<<< orphan*/  i2c_address; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  warn (char*,int,int,int) ; 

__attribute__((used)) static int tda18218_wr_regs(struct tda18218_priv *priv, u8 reg, u8 *val, u8 len)
{
	int ret = 0;
	u8 buf[1+len], quotient, remainder, i, msg_len, msg_len_max;
	struct i2c_msg msg[1] = {
		{
			.addr = priv->cfg->i2c_address,
			.flags = 0,
			.buf = buf,
		}
	};

	msg_len_max = priv->cfg->i2c_wr_max - 1;
	quotient = len / msg_len_max;
	remainder = len % msg_len_max;
	msg_len = msg_len_max;
	for (i = 0; (i <= quotient && remainder); i++) {
		if (i == quotient)  /* set len of the last msg */
			msg_len = remainder;

		msg[0].len = msg_len + 1;
		buf[0] = reg + i * msg_len_max;
		memcpy(&buf[1], &val[i * msg_len_max], msg_len);

		ret = i2c_transfer(priv->i2c, msg, 1);
		if (ret != 1)
			break;
	}

	if (ret == 1) {
		ret = 0;
	} else {
		warn("i2c wr failed ret:%d reg:%02x len:%d", ret, reg, len);
		ret = -EREMOTEIO;
	}

	return ret;
}