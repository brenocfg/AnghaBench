#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_5__ {int isdbs_ts_id; } ;
struct TYPE_6__ {TYPE_2__ dtv_property_cache; } ;
struct va1j5jf8007s_state {int /*<<< orphan*/  adap; TYPE_1__* config; TYPE_3__ fe; } ;
struct i2c_msg {int len; int* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int
va1j5jf8007s_set_ts_id(struct va1j5jf8007s_state *state)
{
	u32 ts_id;
	u8 buf[3];
	struct i2c_msg msg;

	ts_id = state->fe.dtv_property_cache.isdbs_ts_id;
	if (!ts_id)
		return 0;

	buf[0] = 0x8f;
	buf[1] = ts_id >> 8;
	buf[2] = ts_id;

	msg.addr = state->config->demod_address;
	msg.flags = 0;
	msg.len = sizeof(buf);
	msg.buf = buf;

	if (i2c_transfer(state->adap, &msg, 1) != 1)
		return -EREMOTEIO;

	return 0;
}