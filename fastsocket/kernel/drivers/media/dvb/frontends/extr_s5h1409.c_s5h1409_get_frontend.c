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
struct s5h1409_state {int /*<<< orphan*/  current_modulation; int /*<<< orphan*/  current_frequency; } ;
struct TYPE_3__ {int /*<<< orphan*/  modulation; } ;
struct TYPE_4__ {TYPE_1__ vsb; } ;
struct dvb_frontend_parameters {TYPE_2__ u; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {struct s5h1409_state* demodulator_priv; } ;

/* Variables and functions */

__attribute__((used)) static int s5h1409_get_frontend(struct dvb_frontend *fe,
				struct dvb_frontend_parameters *p)
{
	struct s5h1409_state *state = fe->demodulator_priv;

	p->frequency = state->current_frequency;
	p->u.vsb.modulation = state->current_modulation;

	return 0;
}