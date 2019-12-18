#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stv0299_state {TYPE_1__* config; } ;
struct TYPE_6__ {int symbol_rate; } ;
struct TYPE_7__ {TYPE_2__ qpsk; } ;
struct TYPE_8__ {TYPE_3__ u; } ;
struct dvb_frontend_tune_settings {int step_size; int max_drift; TYPE_4__ parameters; int /*<<< orphan*/  min_delay_ms; } ;
struct dvb_frontend {struct stv0299_state* demodulator_priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  min_delay_ms; } ;

/* Variables and functions */

__attribute__((used)) static int stv0299_get_tune_settings(struct dvb_frontend* fe, struct dvb_frontend_tune_settings* fesettings)
{
	struct stv0299_state* state = fe->demodulator_priv;

	fesettings->min_delay_ms = state->config->min_delay_ms;
	if (fesettings->parameters.u.qpsk.symbol_rate < 10000000) {
		fesettings->step_size = fesettings->parameters.u.qpsk.symbol_rate / 32000;
		fesettings->max_drift = 5000;
	} else {
		fesettings->step_size = fesettings->parameters.u.qpsk.symbol_rate / 16000;
		fesettings->max_drift = fesettings->parameters.u.qpsk.symbol_rate / 2000;
	}
	return 0;
}