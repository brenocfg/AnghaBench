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
struct tda10021_state {int pwm; } ;
struct dvb_frontend {TYPE_1__* adapter; struct tda10021_state* demodulator_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  _tda10021_writereg (struct tda10021_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int* tda10021_inittab ; 
 int tda10021_inittab_size ; 

__attribute__((used)) static int tda10021_init (struct dvb_frontend *fe)
{
	struct tda10021_state* state = fe->demodulator_priv;
	int i;

	dprintk("DVB: TDA10021(%d): init chip\n", fe->adapter->num);

	//_tda10021_writereg (fe, 0, 0);

	for (i=0; i<tda10021_inittab_size; i++)
		_tda10021_writereg (state, i, tda10021_inittab[i]);

	_tda10021_writereg (state, 0x34, state->pwm);

	//Comment by markus
	//0x2A[3-0] == PDIV -> P multiplaying factor (P=PDIV+1)(default 0)
	//0x2A[4] == BYPPLL -> Power down mode (default 1)
	//0x2A[5] == LCK -> PLL Lock Flag
	//0x2A[6] == POLAXIN -> Polarity of the input reference clock (default 0)

	//Activate PLL
	_tda10021_writereg(state, 0x2a, tda10021_inittab[0x2a] & 0xef);
	return 0;
}