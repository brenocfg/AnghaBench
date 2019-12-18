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
struct dvb_frontend {struct zl10353_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct zl10353_state {struct dvb_frontend frontend; int /*<<< orphan*/  config; struct i2c_adapter* i2c; } ;
struct zl10353_config {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_ID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ID_CE6230 ; 
 int ID_CE6231 ; 
 int ID_ZL10353 ; 
 int /*<<< orphan*/  kfree (struct zl10353_state*) ; 
 struct zl10353_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct zl10353_config const*,int) ; 
 struct zl10353_config const zl10353_ops ; 
 int zl10353_read_register (struct zl10353_state*,int /*<<< orphan*/ ) ; 

struct dvb_frontend *zl10353_attach(const struct zl10353_config *config,
				    struct i2c_adapter *i2c)
{
	struct zl10353_state *state = NULL;
	int id;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct zl10353_state), GFP_KERNEL);
	if (state == NULL)
		goto error;

	/* setup the state */
	state->i2c = i2c;
	memcpy(&state->config, config, sizeof(struct zl10353_config));

	/* check if the demod is there */
	id = zl10353_read_register(state, CHIP_ID);
	if ((id != ID_ZL10353) && (id != ID_CE6230) && (id != ID_CE6231))
		goto error;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &zl10353_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	return &state->frontend;
error:
	kfree(state);
	return NULL;
}