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
struct dvb_frontend {struct drx397xD_state* demodulator_priv; } ;
struct drx397xD_state {int dummy; } ;
typedef  int fe_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ConfigureMPEGOutput (struct drx397xD_state*,int) ; 
 int /*<<< orphan*/  CorrectSysClockDeviation (struct drx397xD_state*) ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  GetLockStatus (struct drx397xD_state*,int*) ; 

__attribute__((used)) static int drx397x_read_status(struct dvb_frontend *fe, fe_status_t *status)
{
	struct drx397xD_state *s = fe->demodulator_priv;
	int lockstat;

	GetLockStatus(s, &lockstat);

	*status = 0;
	if (lockstat & 2) {
		CorrectSysClockDeviation(s);
		ConfigureMPEGOutput(s, 1);
		*status = FE_HAS_LOCK | FE_HAS_SYNC | FE_HAS_VITERBI;
	}
	if (lockstat & 4)
		*status |= FE_HAS_CARRIER | FE_HAS_SIGNAL;

	return 0;
}