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
struct lgdt3305_state {int current_modulation; TYPE_1__* cfg; } ;
struct dvb_frontend {struct lgdt3305_state* demodulator_priv; } ;
typedef  int /*<<< orphan*/  fe_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  demod_chip; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FE_HAS_CARRIER ; 
 int /*<<< orphan*/  FE_HAS_LOCK ; 
 int /*<<< orphan*/  FE_HAS_SIGNAL ; 
 int /*<<< orphan*/  FE_HAS_SYNC ; 
 int /*<<< orphan*/  FE_HAS_VITERBI ; 
 int /*<<< orphan*/  LGDT3304 ; 
 int /*<<< orphan*/  LGDT3305_GEN_STATUS ; 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int /*<<< orphan*/  lg_dbg (char*,char*,char*,char*,char*,char*) ; 
 scalar_t__ lg_fail (int) ; 
 int lgdt3305_read_cr_lock_status (struct lgdt3305_state*,int*) ; 
 int lgdt3305_read_fec_lock_status (struct lgdt3305_state*,int*) ; 
 int lgdt3305_read_reg (struct lgdt3305_state*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lgdt3305_read_status(struct dvb_frontend *fe, fe_status_t *status)
{
	struct lgdt3305_state *state = fe->demodulator_priv;
	u8 val;
	int ret, signal, inlock, nofecerr, snrgood,
		cr_lock, fec_lock, sync_lock;

	*status = 0;

	ret = lgdt3305_read_reg(state, LGDT3305_GEN_STATUS, &val);
	if (lg_fail(ret))
		goto fail;

	signal    = (val & (1 << 4)) ? 1 : 0;
	inlock    = (val & (1 << 3)) ? 0 : 1;
	sync_lock = (val & (1 << 2)) ? 1 : 0;
	nofecerr  = (val & (1 << 1)) ? 1 : 0;
	snrgood   = (val & (1 << 0)) ? 1 : 0;

	lg_dbg("%s%s%s%s%s\n",
	       signal    ? "SIGNALEXIST " : "",
	       inlock    ? "INLOCK "      : "",
	       sync_lock ? "SYNCLOCK "    : "",
	       nofecerr  ? "NOFECERR "    : "",
	       snrgood   ? "SNRGOOD "     : "");

	ret = lgdt3305_read_cr_lock_status(state, &cr_lock);
	if (lg_fail(ret))
		goto fail;

	if (signal)
		*status |= FE_HAS_SIGNAL;
	if (cr_lock)
		*status |= FE_HAS_CARRIER;
	if (nofecerr)
		*status |= FE_HAS_VITERBI;
	if (sync_lock)
		*status |= FE_HAS_SYNC;

	switch (state->current_modulation) {
	case QAM_256:
	case QAM_64:
		/* signal bit is unreliable on the DT3304 in QAM mode */
		if (((LGDT3304 == state->cfg->demod_chip)) && (cr_lock))
			*status |= FE_HAS_SIGNAL;

		ret = lgdt3305_read_fec_lock_status(state, &fec_lock);
		if (lg_fail(ret))
			goto fail;

		if (fec_lock)
			*status |= FE_HAS_LOCK;
		break;
	case VSB_8:
		if (inlock)
			*status |= FE_HAS_LOCK;
		break;
	default:
		ret = -EINVAL;
	}
fail:
	return ret;
}