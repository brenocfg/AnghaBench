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
typedef  int u16 ;
struct TYPE_4__ {int frequency; } ;
struct TYPE_5__ {TYPE_1__ dtv_property_cache; } ;
struct va1j5jf8007s_state {int /*<<< orphan*/  adap; TYPE_3__* config; TYPE_2__ fe; } ;
struct i2c_msg {int len; int* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int va1j5jf8007s_lookup_cb (int) ; 

__attribute__((used)) static int va1j5jf8007s_set_frequency_1(struct va1j5jf8007s_state *state)
{
	u32 frequency;
	u16 word;
	u8 buf[6];
	struct i2c_msg msg;

	frequency = state->fe.dtv_property_cache.frequency;

	word = (frequency + 500) / 1000;
	if (frequency < 1072000)
		word = (word << 1 & ~0x1f) | (word & 0x0f);

	buf[0] = 0xfe;
	buf[1] = 0xc0;
	buf[2] = 0x40 | word >> 8;
	buf[3] = word;
	buf[4] = 0xe0;
	buf[5] = va1j5jf8007s_lookup_cb(frequency);

	msg.addr = state->config->demod_address;
	msg.flags = 0;
	msg.len = sizeof(buf);
	msg.buf = buf;

	if (i2c_transfer(state->adap, &msg, 1) != 1)
		return -EREMOTEIO;

	return 0;
}