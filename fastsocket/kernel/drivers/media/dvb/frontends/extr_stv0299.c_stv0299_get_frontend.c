#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stv0299_state {TYPE_1__* config; } ;
struct TYPE_5__ {int /*<<< orphan*/  symbol_rate; int /*<<< orphan*/  fec_inner; } ;
struct TYPE_6__ {TYPE_2__ qpsk; } ;
struct dvb_frontend_parameters {int frequency; TYPE_3__ u; int /*<<< orphan*/  inversion; } ;
struct dvb_frontend {struct stv0299_state* demodulator_priv; } ;
typedef  int s32 ;
typedef  scalar_t__ s16 ;
struct TYPE_4__ {int mclk; scalar_t__ invert; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  stv0299_get_fec (struct stv0299_state*) ; 
 int /*<<< orphan*/  stv0299_get_symbolrate (struct stv0299_state*) ; 
 int stv0299_readreg (struct stv0299_state*,int) ; 

__attribute__((used)) static int stv0299_get_frontend(struct dvb_frontend* fe, struct dvb_frontend_parameters * p)
{
	struct stv0299_state* state = fe->demodulator_priv;
	s32 derot_freq;
	int invval;

	derot_freq = (s32)(s16) ((stv0299_readreg (state, 0x22) << 8)
				| stv0299_readreg (state, 0x23));

	derot_freq *= (state->config->mclk >> 16);
	derot_freq += 500;
	derot_freq /= 1000;

	p->frequency += derot_freq;

	invval = stv0299_readreg (state, 0x0c) & 1;
	if (state->config->invert) invval = (~invval) & 1;
	p->inversion = invval ? INVERSION_ON : INVERSION_OFF;

	p->u.qpsk.fec_inner = stv0299_get_fec (state);
	p->u.qpsk.symbol_rate = stv0299_get_symbolrate (state);

	return 0;
}