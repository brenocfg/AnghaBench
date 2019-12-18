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
 int /*<<< orphan*/  MB86A16_DEBUG ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int mb86a16_write(struct mb86a16_state *state, u8 reg, u8 val)
{
	int ret;
	u8 buf[] = { reg, val };

	struct i2c_msg msg = {
		.addr = state->config->demod_address,
		.flags = 0,
		.buf = buf,
		.len = 2
	};

	dprintk(verbose, MB86A16_DEBUG, 1,
		"writing to [0x%02x],Reg[0x%02x],Data[0x%02x]",
		state->config->demod_address, buf[0], buf[1]);

	ret = i2c_transfer(state->i2c_adap, &msg, 1);

	return (ret != 1) ? -EREMOTEIO : 0;
}