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
struct tda1002x_config {int /*<<< orphan*/  demod_address; } ;
struct dvb_frontend {struct tda10021_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct tda10021_state {int pwm; struct dvb_frontend frontend; struct tda1002x_config const* config; int /*<<< orphan*/  reg0; struct i2c_adapter* i2c; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct tda10021_state*) ; 
 struct tda10021_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * tda10021_inittab ; 
 int /*<<< orphan*/  tda10021_ops ; 
 int tda10021_readreg (struct tda10021_state*,int) ; 

struct dvb_frontend* tda10021_attach(const struct tda1002x_config* config,
				     struct i2c_adapter* i2c,
				     u8 pwm)
{
	struct tda10021_state* state = NULL;
	u8 id;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct tda10021_state), GFP_KERNEL);
	if (state == NULL) goto error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->pwm = pwm;
	state->reg0 = tda10021_inittab[0];

	/* check if the demod is there */
	id = tda10021_readreg(state, 0x1a);
	if ((id & 0xf0) != 0x70) goto error;

	/* Don't claim TDA10023 */
	if (id == 0x7d)
		goto error;

	printk("TDA10021: i2c-addr = 0x%02x, id = 0x%02x\n",
	       state->config->demod_address, id);

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &tda10021_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;

error:
	kfree(state);
	return NULL;
}