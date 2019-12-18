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
struct dvb_frontend {struct nxt200x_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct nxt200x_state {int demod_chip; struct dvb_frontend frontend; scalar_t__ initialised; struct i2c_adapter* i2c; struct nxt200x_config const* config; } ;
struct nxt200x_config {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  NXT2002 129 
#define  NXT2004 128 
 int /*<<< orphan*/  dprintk (char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  kfree (struct nxt200x_state*) ; 
 struct nxt200x_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nxt200x_ops ; 
 int /*<<< orphan*/  nxt200x_readbytes (struct nxt200x_state*,int,int*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

struct dvb_frontend* nxt200x_attach(const struct nxt200x_config* config,
				   struct i2c_adapter* i2c)
{
	struct nxt200x_state* state = NULL;
	u8 buf [] = {0,0,0,0,0};

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct nxt200x_state), GFP_KERNEL);
	if (state == NULL)
		goto error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initialised = 0;

	/* read card id */
	nxt200x_readbytes(state, 0x00, buf, 5);
	dprintk("NXT info: %02X %02X %02X %02X %02X\n",
		buf[0], buf[1], buf[2],	buf[3], buf[4]);

	/* set demod chip */
	switch (buf[0]) {
		case 0x04:
			state->demod_chip = NXT2002;
			printk("nxt200x: NXT2002 Detected\n");
			break;
		case 0x05:
			state->demod_chip = NXT2004;
			printk("nxt200x: NXT2004 Detected\n");
			break;
		default:
			goto error;
	}

	/* make sure demod chip is supported */
	switch (state->demod_chip) {
		case NXT2002:
			if (buf[0] != 0x04) goto error;		/* device id */
			if (buf[1] != 0x02) goto error;		/* fab id */
			if (buf[2] != 0x11) goto error;		/* month */
			if (buf[3] != 0x20) goto error;		/* year msb */
			if (buf[4] != 0x00) goto error;		/* year lsb */
			break;
		case NXT2004:
			if (buf[0] != 0x05) goto error;		/* device id */
			break;
		default:
			goto error;
	}

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &nxt200x_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;

error:
	kfree(state);
	printk("Unknown/Unsupported NXT chip: %02X %02X %02X %02X %02X\n",
		buf[0], buf[1], buf[2], buf[3], buf[4]);
	return NULL;
}