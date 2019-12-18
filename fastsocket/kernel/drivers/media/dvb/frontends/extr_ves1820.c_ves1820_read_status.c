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
struct ves1820_state {int dummy; } ;
struct dvb_frontend {struct ves1820_state* demodulator_priv; } ;
typedef  int /*<<< orphan*/  fe_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  FE_HAS_CARRIER ; 
 int /*<<< orphan*/  FE_HAS_LOCK ; 
 int /*<<< orphan*/  FE_HAS_SIGNAL ; 
 int /*<<< orphan*/  FE_HAS_SYNC ; 
 int /*<<< orphan*/  FE_HAS_VITERBI ; 
 int ves1820_readreg (struct ves1820_state*,int) ; 

__attribute__((used)) static int ves1820_read_status(struct dvb_frontend* fe, fe_status_t* status)
{
	struct ves1820_state* state = fe->demodulator_priv;
	int sync;

	*status = 0;
	sync = ves1820_readreg(state, 0x11);

	if (sync & 1)
		*status |= FE_HAS_SIGNAL;

	if (sync & 2)
		*status |= FE_HAS_CARRIER;

	if (sync & 2)	/* XXX FIXME! */
		*status |= FE_HAS_VITERBI;

	if (sync & 4)
		*status |= FE_HAS_SYNC;

	if (sync & 8)
		*status |= FE_HAS_LOCK;

	return 0;
}