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
typedef  int u8 ;
struct lgdt3305_state {int current_modulation; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LGDT3305_FEC_LOCK_STATUS ; 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int /*<<< orphan*/  lg_dbg (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  lg_fail (int) ; 
 int lgdt3305_read_reg (struct lgdt3305_state*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lgdt3305_read_fec_lock_status(struct lgdt3305_state *state,
					 int *locked)
{
	u8 val;
	int ret, mpeg_lock, fec_lock, viterbi_lock;

	*locked = 0;

	switch (state->current_modulation) {
	case QAM_256:
	case QAM_64:
		ret = lgdt3305_read_reg(state,
					LGDT3305_FEC_LOCK_STATUS, &val);
		if (lg_fail(ret))
			goto fail;

		mpeg_lock    = (val & (1 << 0)) ? 1 : 0;
		fec_lock     = (val & (1 << 2)) ? 1 : 0;
		viterbi_lock = (val & (1 << 3)) ? 1 : 0;

		*locked = mpeg_lock && fec_lock && viterbi_lock;

		lg_dbg("(%d) %s%s%s\n", *locked,
		       mpeg_lock    ? "mpeg lock  "  : "",
		       fec_lock     ? "fec lock  "   : "",
		       viterbi_lock ? "viterbi lock" : "");
		break;
	case VSB_8:
	default:
		ret = -EINVAL;
	}
fail:
	return ret;
}