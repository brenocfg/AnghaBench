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
struct dvb_frontend {struct cx22700_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct cx22700_state {struct dvb_frontend frontend; struct i2c_adapter* i2c; struct cx22700_config const* config; } ;
struct cx22700_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cx22700_ops ; 
 scalar_t__ cx22700_readreg (struct cx22700_state*,int) ; 
 int /*<<< orphan*/  kfree (struct cx22700_state*) ; 
 struct cx22700_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

struct dvb_frontend* cx22700_attach(const struct cx22700_config* config,
				    struct i2c_adapter* i2c)
{
	struct cx22700_state* state = NULL;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct cx22700_state), GFP_KERNEL);
	if (state == NULL) goto error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check if the demod is there */
	if (cx22700_readreg(state, 0x07) < 0) goto error;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &cx22700_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;

error:
	kfree(state);
	return NULL;
}