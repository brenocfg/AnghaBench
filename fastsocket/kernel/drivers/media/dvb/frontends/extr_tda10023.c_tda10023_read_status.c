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
struct tda10023_state {int dummy; } ;
struct dvb_frontend {struct tda10023_state* demodulator_priv; } ;
typedef  int fe_status_t ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int tda10023_readreg (struct tda10023_state*,int) ; 

__attribute__((used)) static int tda10023_read_status(struct dvb_frontend* fe, fe_status_t* status)
{
	struct tda10023_state* state = fe->demodulator_priv;
	int sync;

	*status = 0;

	//0x11[1] == CARLOCK -> Carrier locked
	//0x11[2] == FSYNC -> Frame synchronisation
	//0x11[3] == FEL -> Front End locked
	//0x11[6] == NODVB -> DVB Mode Information
	sync = tda10023_readreg (state, 0x11);

	if (sync & 2)
		*status |= FE_HAS_SIGNAL|FE_HAS_CARRIER;

	if (sync & 4)
		*status |= FE_HAS_SYNC|FE_HAS_VITERBI;

	if (sync & 8)
		*status |= FE_HAS_LOCK;

	return 0;
}