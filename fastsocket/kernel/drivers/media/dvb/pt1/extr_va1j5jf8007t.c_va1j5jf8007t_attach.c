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
struct dvb_frontend {struct va1j5jf8007t_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct va1j5jf8007t_state {struct i2c_adapter* adap; struct va1j5jf8007t_config const* config; struct dvb_frontend fe; } ;
struct va1j5jf8007t_config {int /*<<< orphan*/  demod_address; } ;
struct i2c_msg {int len; int* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  kfree (struct va1j5jf8007t_state*) ; 
 struct va1j5jf8007t_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  va1j5jf8007t_ops ; 

struct dvb_frontend *
va1j5jf8007t_attach(const struct va1j5jf8007t_config *config,
		    struct i2c_adapter *adap)
{
	struct va1j5jf8007t_state *state;
	struct dvb_frontend *fe;
	u8 buf[2];
	struct i2c_msg msg;

	state = kzalloc(sizeof(struct va1j5jf8007t_state), GFP_KERNEL);
	if (!state)
		return NULL;

	state->config = config;
	state->adap = adap;

	fe = &state->fe;
	memcpy(&fe->ops, &va1j5jf8007t_ops, sizeof(struct dvb_frontend_ops));
	fe->demodulator_priv = state;

	buf[0] = 0x01;
	buf[1] = 0x80;

	msg.addr = state->config->demod_address;
	msg.flags = 0;
	msg.len = sizeof(buf);
	msg.buf = buf;

	if (i2c_transfer(state->adap, &msg, 1) != 1) {
		kfree(state);
		return NULL;
	}

	return fe;
}