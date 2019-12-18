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
struct dvb_frontend {struct nxt6000_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct nxt6000_state {struct dvb_frontend frontend; struct i2c_adapter* i2c; struct nxt6000_config const* config; } ;
struct nxt6000_config {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NXT6000ASICDEVICE ; 
 int /*<<< orphan*/  OFDM_MSC_REV ; 
 int /*<<< orphan*/  kfree (struct nxt6000_state*) ; 
 struct nxt6000_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nxt6000_ops ; 
 scalar_t__ nxt6000_readreg (struct nxt6000_state*,int /*<<< orphan*/ ) ; 

struct dvb_frontend* nxt6000_attach(const struct nxt6000_config* config,
				    struct i2c_adapter* i2c)
{
	struct nxt6000_state* state = NULL;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct nxt6000_state), GFP_KERNEL);
	if (state == NULL) goto error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check if the demod is there */
	if (nxt6000_readreg(state, OFDM_MSC_REV) != NXT6000ASICDEVICE) goto error;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &nxt6000_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;

error:
	kfree(state);
	return NULL;
}