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
typedef  int /*<<< orphan*/  u8 ;
struct mb86a16_state {int /*<<< orphan*/  i2c_adap; TYPE_1__* config; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int mb86a16_read(struct mb86a16_state *state, u8 reg, u8 *val)
{
	int ret;
	u8 b0[] = { reg };
	u8 b1[] = { 0 };

	struct i2c_msg msg[] = {
		{
			.addr = state->config->demod_address,
			.flags = 0,
			.buf = b0,
			.len = 1
		}, {
			.addr = state->config->demod_address,
			.flags = I2C_M_RD,
			.buf = b1,
			.len = 1
		}
	};
	ret = i2c_transfer(state->i2c_adap, msg, 2);
	if (ret != 2) {
		dprintk(verbose, MB86A16_ERROR, 1, "read error(reg=0x%02x, ret=0x%i)",
			reg, ret);

		return -EREMOTEIO;
	}
	*val = b1[0];

	return ret;
}