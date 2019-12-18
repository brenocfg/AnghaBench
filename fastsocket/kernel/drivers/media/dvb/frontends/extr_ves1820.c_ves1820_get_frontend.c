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
struct ves1820_state {int reg0; TYPE_1__* config; } ;
struct TYPE_5__ {scalar_t__ symbol_rate; int /*<<< orphan*/  fec_inner; scalar_t__ modulation; } ;
struct TYPE_6__ {TYPE_2__ qam; } ;
struct dvb_frontend_parameters {int frequency; TYPE_3__ u; void* inversion; } ;
struct dvb_frontend {struct ves1820_state* demodulator_priv; } ;
typedef  int s8 ;
typedef  int s32 ;
struct TYPE_4__ {int /*<<< orphan*/  invert; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_NONE ; 
 void* INVERSION_OFF ; 
 void* INVERSION_ON ; 
 scalar_t__ QAM_16 ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 scalar_t__ verbose ; 
 int ves1820_readreg (struct ves1820_state*,int) ; 

__attribute__((used)) static int ves1820_get_frontend(struct dvb_frontend* fe, struct dvb_frontend_parameters *p)
{
	struct ves1820_state* state = fe->demodulator_priv;
	int sync;
	s8 afc = 0;

	sync = ves1820_readreg(state, 0x11);
	afc = ves1820_readreg(state, 0x19);
	if (verbose) {
		/* AFC only valid when carrier has been recovered */
		printk(sync & 2 ? "ves1820: AFC (%d) %dHz\n" :
			"ves1820: [AFC (%d) %dHz]\n", afc, -((s32) p->u.qam.symbol_rate * afc) >> 10);
	}

	if (!state->config->invert) {
		p->inversion = (state->reg0 & 0x20) ? INVERSION_ON : INVERSION_OFF;
	} else {
		p->inversion = (!(state->reg0 & 0x20)) ? INVERSION_ON : INVERSION_OFF;
	}

	p->u.qam.modulation = ((state->reg0 >> 2) & 7) + QAM_16;

	p->u.qam.fec_inner = FEC_NONE;

	p->frequency = ((p->frequency + 31250) / 62500) * 62500;
	if (sync & 2)
		p->frequency -= ((s32) p->u.qam.symbol_rate * afc) >> 10;

	return 0;
}