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
struct l64781_state {int dummy; } ;
struct dvb_frontend {struct l64781_state* demodulator_priv; } ;
typedef  int /*<<< orphan*/  fe_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  FE_HAS_CARRIER ; 
 int /*<<< orphan*/  FE_HAS_LOCK ; 
 int /*<<< orphan*/  FE_HAS_SIGNAL ; 
 int /*<<< orphan*/  FE_HAS_SYNC ; 
 int /*<<< orphan*/  FE_HAS_VITERBI ; 
 int l64781_readreg (struct l64781_state*,int) ; 

__attribute__((used)) static int l64781_read_status(struct dvb_frontend* fe, fe_status_t* status)
{
	struct l64781_state* state = fe->demodulator_priv;
	int sync = l64781_readreg (state, 0x32);
	int gain = l64781_readreg (state, 0x0e);

	l64781_readreg (state, 0x00);  /*  clear interrupt registers... */
	l64781_readreg (state, 0x01);  /*  dto. */

	*status = 0;

	if (gain > 5)
		*status |= FE_HAS_SIGNAL;

	if (sync & 0x02) /* VCXO locked, this criteria should be ok */
		*status |= FE_HAS_CARRIER;

	if (sync & 0x20)
		*status |= FE_HAS_VITERBI;

	if (sync & 0x40)
		*status |= FE_HAS_SYNC;

	if (sync == 0x7f)
		*status |= FE_HAS_LOCK;

	return 0;
}