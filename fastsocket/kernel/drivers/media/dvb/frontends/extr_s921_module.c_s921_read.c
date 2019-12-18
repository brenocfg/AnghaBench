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
typedef  int u8 ;
struct s921_state {int /*<<< orphan*/  i2c; int /*<<< orphan*/  addr; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int s921_read(void *dev, u8 reg) {
	struct s921_state *state = dev;
	u8 b1;
	int ret;
	struct i2c_msg msg[2] = { { .addr = state->addr,
				    .flags = 0,
				    .buf = &reg, .len = 1 },
				  { .addr = state->addr,
				    .flags = I2C_M_RD,
				    .buf = &b1, .len = 1 } };

	ret = i2c_transfer(state->i2c, msg, 2);
	if (ret != 2)
		return ret;
	return b1;
}