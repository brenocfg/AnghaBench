#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dvb_frontend {struct s921_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct TYPE_2__ {struct s921_state* priv_dev; int /*<<< orphan*/ * i2c_read; int /*<<< orphan*/ * i2c_write; } ;
struct s921_state {struct dvb_frontend frontend; TYPE_1__ dev; struct i2c_adapter* i2c; int /*<<< orphan*/  addr; } ;
struct s921_config {int /*<<< orphan*/  i2c_address; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISDB_T_CMD_INIT ; 
 int /*<<< orphan*/  demod_s921 ; 
 struct s921_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  s921_isdb_cmd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s921_read ; 
 int /*<<< orphan*/  s921_write ; 

struct dvb_frontend* s921_attach(const struct s921_config *config,
					   struct i2c_adapter *i2c)
{

	struct s921_state *state;
	state = kzalloc(sizeof(struct s921_state), GFP_KERNEL);
	if (state == NULL)
		return NULL;

	state->addr = config->i2c_address;
	state->i2c = i2c;
	state->dev.i2c_write = &s921_write;
	state->dev.i2c_read = &s921_read;
	state->dev.priv_dev = state;

	s921_isdb_cmd(&state->dev, ISDB_T_CMD_INIT, NULL);

	memcpy(&state->frontend.ops, &demod_s921, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;
}