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
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;
struct dvb_frontend {struct drx397xD_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct drx397xD_state {struct dvb_frontend frontend; int /*<<< orphan*/  config; struct i2c_adapter* i2c; } ;
struct drx397xD_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RD16 (struct drx397xD_state*,int) ; 
 struct drx397xD_config const drx397x_ops ; 
 int /*<<< orphan*/  kfree (struct drx397xD_state*) ; 
 struct drx397xD_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct drx397xD_config const*,int) ; 

struct dvb_frontend *drx397xD_attach(const struct drx397xD_config *config,
				     struct i2c_adapter *i2c)
{
	struct drx397xD_state *state;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct drx397xD_state), GFP_KERNEL);
	if (!state)
		goto error;

	/* setup the state */
	state->i2c = i2c;
	memcpy(&state->config, config, sizeof(struct drx397xD_config));

	/* check if the demod is there */
	if (RD16(state, 0x2410019) < 0)
		goto error;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &drx397x_ops,
			sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	return &state->frontend;
error:
	kfree(state);

	return NULL;
}