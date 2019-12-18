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
struct zl10353_state {int dummy; } ;
struct dvb_frontend {struct zl10353_state* demodulator_priv; } ;
typedef  int fe_status_t ;

/* Variables and functions */
 int EREMOTEIO ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  STATUS_6 ; 
 int /*<<< orphan*/  STATUS_7 ; 
 int /*<<< orphan*/  STATUS_8 ; 
 int zl10353_read_register (struct zl10353_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zl10353_read_status(struct dvb_frontend *fe, fe_status_t *status)
{
	struct zl10353_state *state = fe->demodulator_priv;
	int s6, s7, s8;

	if ((s6 = zl10353_read_register(state, STATUS_6)) < 0)
		return -EREMOTEIO;
	if ((s7 = zl10353_read_register(state, STATUS_7)) < 0)
		return -EREMOTEIO;
	if ((s8 = zl10353_read_register(state, STATUS_8)) < 0)
		return -EREMOTEIO;

	*status = 0;
	if (s6 & (1 << 2))
		*status |= FE_HAS_CARRIER;
	if (s6 & (1 << 1))
		*status |= FE_HAS_VITERBI;
	if (s6 & (1 << 5))
		*status |= FE_HAS_LOCK;
	if (s7 & (1 << 4))
		*status |= FE_HAS_SYNC;
	if (s8 & (1 << 6))
		*status |= FE_HAS_SIGNAL;

	if ((*status & (FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC)) !=
	    (FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC))
		*status &= ~FE_HAS_LOCK;

	return 0;
}