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
struct lgdt3305_state {int /*<<< orphan*/  current_frequency; int /*<<< orphan*/  current_modulation; } ;
struct TYPE_3__ {int /*<<< orphan*/  modulation; } ;
struct TYPE_4__ {TYPE_1__ vsb; } ;
struct dvb_frontend_parameters {int /*<<< orphan*/  frequency; TYPE_2__ u; } ;
struct dvb_frontend {struct lgdt3305_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  lg_dbg (char*) ; 

__attribute__((used)) static int lgdt3305_get_frontend(struct dvb_frontend *fe,
				 struct dvb_frontend_parameters *param)
{
	struct lgdt3305_state *state = fe->demodulator_priv;

	lg_dbg("\n");

	param->u.vsb.modulation = state->current_modulation;
	param->frequency = state->current_frequency;
	return 0;
}