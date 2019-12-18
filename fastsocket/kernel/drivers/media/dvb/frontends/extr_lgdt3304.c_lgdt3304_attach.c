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
struct dvb_frontend {struct lgdt3304_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct lgdt3304_state {struct dvb_frontend frontend; struct i2c_adapter* i2c; int /*<<< orphan*/  addr; } ;
struct lgdt3304_config {int /*<<< orphan*/  i2c_address; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  demod_lgdt3304 ; 
 struct lgdt3304_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

struct dvb_frontend* lgdt3304_attach(const struct lgdt3304_config *config,
					   struct i2c_adapter *i2c)
{

	struct lgdt3304_state *state;
	state = kzalloc(sizeof(struct lgdt3304_state), GFP_KERNEL);
	if (state == NULL)
		return NULL;
	state->addr = config->i2c_address;
	state->i2c = i2c;

	memcpy(&state->frontend.ops, &demod_lgdt3304, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;
}