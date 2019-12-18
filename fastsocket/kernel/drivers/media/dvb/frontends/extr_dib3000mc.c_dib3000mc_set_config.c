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
struct dvb_frontend {struct dib3000mc_state* demodulator_priv; } ;
struct dib3000mc_state {struct dib3000mc_config* cfg; } ;
struct dib3000mc_config {int dummy; } ;

/* Variables and functions */

void dib3000mc_set_config(struct dvb_frontend *fe, struct dib3000mc_config *cfg)
{
	struct dib3000mc_state *state = fe->demodulator_priv;
	state->cfg = cfg;
}