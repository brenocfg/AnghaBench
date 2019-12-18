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
struct va1j5jf8007t_state {int /*<<< orphan*/  adap; TYPE_1__* config; } ;
struct i2c_msg {int len; int* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int va1j5jf8007t_init_frequency(struct va1j5jf8007t_state *state)
{
	u8 buf[7];
	struct i2c_msg msg;

	buf[0] = 0xfe;
	buf[1] = 0xc2;
	buf[2] = 0x01;
	buf[3] = 0x8f;
	buf[4] = 0xc1;
	buf[5] = 0x80;
	buf[6] = 0x80;

	msg.addr = state->config->demod_address;
	msg.flags = 0;
	msg.len = sizeof(buf);
	msg.buf = buf;

	if (i2c_transfer(state->adap, &msg, 1) != 1)
		return -EREMOTEIO;

	return 0;
}