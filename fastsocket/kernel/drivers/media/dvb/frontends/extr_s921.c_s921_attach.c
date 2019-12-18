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
struct dvb_frontend {struct s921_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct s921_state {struct dvb_frontend frontend; struct i2c_adapter* i2c; struct s921_config const* config; } ;
struct s921_config {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  kfree (struct s921_state*) ; 
 struct s921_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rc (char*) ; 
 int /*<<< orphan*/  s921_ops ; 

struct dvb_frontend *s921_attach(const struct s921_config *config,
				    struct i2c_adapter *i2c)
{
	/* allocate memory for the internal state */
	struct s921_state *state =
		kzalloc(sizeof(struct s921_state), GFP_KERNEL);

	dprintk("\n");
	if (state == NULL) {
		rc("Unable to kzalloc\n");
		goto rcor;
	}

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &s921_ops,
		sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	return &state->frontend;

rcor:
	kfree(state);

	return NULL;
}