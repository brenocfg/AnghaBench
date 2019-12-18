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
struct dvb_frontend {struct ttusbdecfe_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct ttusbdecfe_state {struct dvb_frontend frontend; scalar_t__ hi_band; scalar_t__ voltage; struct ttusbdecfe_config const* config; } ;
struct ttusbdecfe_config {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ttusbdecfe_state* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttusbdecfe_dvbs_ops ; 

struct dvb_frontend* ttusbdecfe_dvbs_attach(const struct ttusbdecfe_config* config)
{
	struct ttusbdecfe_state* state = NULL;

	/* allocate memory for the internal state */
	state = kmalloc(sizeof(struct ttusbdecfe_state), GFP_KERNEL);
	if (state == NULL)
		return NULL;

	/* setup the state */
	state->config = config;
	state->voltage = 0;
	state->hi_band = 0;

	/* create dvb_frontend */
	memcpy(&state->frontend.ops, &ttusbdecfe_dvbs_ops, sizeof(struct dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	return &state->frontend;
}