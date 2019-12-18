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
struct TYPE_3__ {int /*<<< orphan*/  fec_inner; } ;
struct TYPE_4__ {TYPE_1__ qpsk; } ;
struct dvb_frontend_parameters {unsigned int frequency; TYPE_2__ u; int /*<<< orphan*/  inversion; } ;
struct dvb_frontend {struct cx24110_state* demodulator_priv; } ;
struct cx24110_state {int dummy; } ;
typedef  unsigned int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  cx24110_get_fec (struct cx24110_state*) ; 
 int cx24110_readreg (struct cx24110_state*,int) ; 

__attribute__((used)) static int cx24110_get_frontend(struct dvb_frontend* fe, struct dvb_frontend_parameters *p)
{
	struct cx24110_state *state = fe->demodulator_priv;
	s32 afc; unsigned sclk;

/* cannot read back tuner settings (freq). Need to have some private storage */

	sclk = cx24110_readreg (state, 0x07) & 0x03;
/* ok, real AFC (FEDR) freq. is afc/2^24*fsamp, fsamp=45/60/80/90MHz.
 * Need 64 bit arithmetic. Is thiss possible in the kernel? */
	if (sclk==0) sclk=90999000L/2L;
	else if (sclk==1) sclk=60666000L;
	else if (sclk==2) sclk=80888000L;
	else sclk=90999000L;
	sclk>>=8;
	afc = sclk*(cx24110_readreg (state, 0x44)&0x1f)+
	      ((sclk*cx24110_readreg (state, 0x45))>>8)+
	      ((sclk*cx24110_readreg (state, 0x46))>>16);

	p->frequency += afc;
	p->inversion = (cx24110_readreg (state, 0x22) & 0x10) ?
				INVERSION_ON : INVERSION_OFF;
	p->u.qpsk.fec_inner = cx24110_get_fec (state);

	return 0;
}