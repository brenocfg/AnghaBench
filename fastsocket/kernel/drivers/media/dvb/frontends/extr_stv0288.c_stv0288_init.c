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
typedef  int u8 ;
struct stv0288_state {TYPE_1__* config; } ;
struct dvb_frontend {struct stv0288_state* demodulator_priv; } ;
struct TYPE_2__ {int* inittab; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int* stv0288_inittab ; 
 int /*<<< orphan*/  stv0288_writeregI (struct stv0288_state*,int,int) ; 

__attribute__((used)) static int stv0288_init(struct dvb_frontend *fe)
{
	struct stv0288_state *state = fe->demodulator_priv;
	int i;
	u8 reg;
	u8 val;

	dprintk("stv0288: init chip\n");
	stv0288_writeregI(state, 0x41, 0x04);
	msleep(50);

	/* we have default inittab */
	if (state->config->inittab == NULL) {
		for (i = 0; !(stv0288_inittab[i] == 0xff &&
				stv0288_inittab[i + 1] == 0xff); i += 2)
			stv0288_writeregI(state, stv0288_inittab[i],
					stv0288_inittab[i + 1]);
	} else {
		for (i = 0; ; i += 2)  {
			reg = state->config->inittab[i];
			val = state->config->inittab[i+1];
			if (reg == 0xff && val == 0xff)
				break;
			stv0288_writeregI(state, reg, val);
		}
	}
	return 0;
}