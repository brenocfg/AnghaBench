#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* dvb; } ;
struct tda10021_state {int reg0; TYPE_3__* config; TYPE_2__ frontend; } ;
struct TYPE_9__ {scalar_t__ symbol_rate; int /*<<< orphan*/  fec_inner; scalar_t__ modulation; } ;
struct TYPE_10__ {TYPE_4__ qam; } ;
struct dvb_frontend_parameters {int frequency; TYPE_5__ u; int /*<<< orphan*/  inversion; } ;
struct dvb_frontend {struct tda10021_state* demodulator_priv; } ;
typedef  int s8 ;
typedef  int s32 ;
struct TYPE_8__ {scalar_t__ invert; } ;
struct TYPE_6__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_NONE ; 
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 scalar_t__ QAM_16 ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int,int) ; 
 int tda10021_readreg (struct tda10021_state*,int) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int tda10021_get_frontend(struct dvb_frontend* fe, struct dvb_frontend_parameters *p)
{
	struct tda10021_state* state = fe->demodulator_priv;
	int sync;
	s8 afc = 0;

	sync = tda10021_readreg(state, 0x11);
	afc = tda10021_readreg(state, 0x19);
	if (verbose) {
		/* AFC only valid when carrier has been recovered */
		printk(sync & 2 ? "DVB: TDA10021(%d): AFC (%d) %dHz\n" :
				  "DVB: TDA10021(%d): [AFC (%d) %dHz]\n",
			state->frontend.dvb->num, afc,
		       -((s32)p->u.qam.symbol_rate * afc) >> 10);
	}

	p->inversion = ((state->reg0 & 0x20) == 0x20) ^ (state->config->invert != 0) ? INVERSION_ON : INVERSION_OFF;
	p->u.qam.modulation = ((state->reg0 >> 2) & 7) + QAM_16;

	p->u.qam.fec_inner = FEC_NONE;
	p->frequency = ((p->frequency + 31250) / 62500) * 62500;

	if (sync & 2)
		p->frequency -= ((s32)p->u.qam.symbol_rate * afc) >> 10;

	return 0;
}