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
struct dvb_frontend {struct l64781_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct l64781_state {int first; struct dvb_frontend frontend; struct i2c_adapter* i2c; struct l64781_config const* config; } ;
struct l64781_config {int /*<<< orphan*/  demod_address; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  kfree (struct l64781_state*) ; 
 struct l64781_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l64781_ops ; 
 int l64781_readreg (struct l64781_state*,int) ; 
 int /*<<< orphan*/  l64781_writereg (struct l64781_state*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ reset_and_configure (struct l64781_state*) ; 

struct dvb_frontend* l64781_attach(const struct l64781_config* config,
				   struct i2c_adapter* i2c)
{
	struct l64781_state* state = NULL;
	int reg0x3e = -1;
	u8 b0 [] = { 0x1a };
	u8 b1 [] = { 0x00 };
	struct i2c_msg msg [] = { { .addr = config->demod_address, .flags = 0, .buf = b0, .len = 1 },
			   { .addr = config->demod_address, .flags = I2C_M_RD, .buf = b1, .len = 1 } };

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct l64781_state), GFP_KERNEL);
	if (state == NULL) goto error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->first = 1;

	/**
	 *  the L64781 won't show up before we send the reset_and_configure()
	 *  broadcast. If nothing responds there is no L64781 on the bus...
	 */
	if (reset_and_configure(state) < 0) {
		dprintk("No response to reset and configure broadcast...\n");
		goto error;
	}

	/* The chip always responds to reads */
	if (i2c_transfer(state->i2c, msg, 2) != 2) {
		dprintk("No response to read on I2C bus\n");
		goto error;
	}

	/* Save current register contents for bailout */
	reg0x3e = l64781_readreg(state, 0x3e);

	/* Reading the POWER_DOWN register always returns 0 */
	if (reg0x3e != 0) {
		dprintk("Device doesn't look like L64781\n");
		goto error;
	}

	/* Turn the chip off */
	l64781_writereg (state, 0x3e, 0x5a);

	/* Responds to all reads with 0 */
	if (l64781_readreg(state, 0x1a) != 0) {
		dprintk("Read 1 returned unexpcted value\n");
		goto error;
	}

	/* Turn the chip on */
	l64781_writereg (state, 0x3e, 0xa5);

	/* Responds with register default value */
	if (l64781_readreg(state, 0x1a) != 0xa1) {
		dprintk("Read 2 returned unexpcted value\n");
		goto error;
	}

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &l64781_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;

error:
	if (reg0x3e >= 0)
		l64781_writereg (state, 0x3e, reg0x3e);  /* restore reg 0x3e */
	kfree(state);
	return NULL;
}