#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int symbol_rate_min; int symbol_rate_max; } ;
struct TYPE_4__ {TYPE_1__ info; } ;
struct dvb_frontend {struct ves1820_state* demodulator_priv; TYPE_2__ ops; } ;
struct ves1820_state {struct dvb_frontend frontend; struct ves1820_config const* config; int /*<<< orphan*/  pwm; struct i2c_adapter* i2c; int /*<<< orphan*/  reg0; } ;
struct ves1820_config {int xin; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct ves1820_state*) ; 
 struct ves1820_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/ * ves1820_inittab ; 
 int /*<<< orphan*/  ves1820_ops ; 
 int ves1820_readreg (struct ves1820_state*,int) ; 

struct dvb_frontend* ves1820_attach(const struct ves1820_config* config,
				    struct i2c_adapter* i2c,
				    u8 pwm)
{
	struct ves1820_state* state = NULL;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct ves1820_state), GFP_KERNEL);
	if (state == NULL)
		goto error;

	/* setup the state */
	state->reg0 = ves1820_inittab[0];
	state->config = config;
	state->i2c = i2c;
	state->pwm = pwm;

	/* check if the demod is there */
	if ((ves1820_readreg(state, 0x1a) & 0xf0) != 0x70)
		goto error;

	if (verbose)
		printk("ves1820: pwm=0x%02x\n", state->pwm);

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &ves1820_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.ops.info.symbol_rate_min = (state->config->xin / 2) / 64;      /* SACLK/64 == (XIN/2)/64 */
	state->frontend.ops.info.symbol_rate_max = (state->config->xin / 2) / 4;       /* SACLK/4 */
	state->frontend.demodulator_priv = state;

	return &state->frontend;

error:
	kfree(state);
	return NULL;
}