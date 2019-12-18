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
typedef  int u16 ;
struct sp887x_state {int dummy; } ;
struct dvb_frontend {struct sp887x_state* demodulator_priv; } ;
typedef  int fe_status_t ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int sp887x_readreg (struct sp887x_state*,int) ; 

__attribute__((used)) static int sp887x_read_status(struct dvb_frontend* fe, fe_status_t* status)
{
	struct sp887x_state* state = fe->demodulator_priv;
	u16 snr12 = sp887x_readreg(state, 0xf16);
	u16 sync0x200 = sp887x_readreg(state, 0x200);
	u16 sync0xf17 = sp887x_readreg(state, 0xf17);

	*status = 0;

	if (snr12 > 0x00f)
		*status |= FE_HAS_SIGNAL;

	//if (sync0x200 & 0x004)
	//	*status |= FE_HAS_SYNC | FE_HAS_CARRIER;

	//if (sync0x200 & 0x008)
	//	*status |= FE_HAS_VITERBI;

	if ((sync0xf17 & 0x00f) == 0x002) {
		*status |= FE_HAS_LOCK;
		*status |= FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_CARRIER;
	}

	if (sync0x200 & 0x001) {	/* tuner adjustment requested...*/
		int steps = (sync0x200 >> 4) & 0x00f;
		if (steps & 0x008)
			steps = -steps;
		dprintk("sp887x: implement tuner adjustment (%+i steps)!!\n",
		       steps);
	}

	return 0;
}