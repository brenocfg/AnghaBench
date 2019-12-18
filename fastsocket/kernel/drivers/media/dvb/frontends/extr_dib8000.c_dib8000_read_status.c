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
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {int dummy; } ;
typedef  int /*<<< orphan*/  fe_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  FE_HAS_CARRIER ; 
 int /*<<< orphan*/  FE_HAS_LOCK ; 
 int /*<<< orphan*/  FE_HAS_SIGNAL ; 
 int /*<<< orphan*/  FE_HAS_SYNC ; 
 int /*<<< orphan*/  FE_HAS_VITERBI ; 
 int dib8000_read_word (struct dib8000_state*,int) ; 

__attribute__((used)) static int dib8000_read_status(struct dvb_frontend *fe, fe_status_t * stat)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u16 lock = dib8000_read_word(state, 568);

	*stat = 0;

	if ((lock >> 13) & 1)
		*stat |= FE_HAS_SIGNAL;

	if ((lock >> 8) & 1) /* Equal */
		*stat |= FE_HAS_CARRIER;

	if (((lock >> 1) & 0xf) == 0xf) /* TMCC_SYNC */
		*stat |= FE_HAS_SYNC;

	if (((lock >> 12) & 1) && ((lock >> 5) & 7)) /* FEC MPEG */
		*stat |= FE_HAS_LOCK;

	if ((lock >> 12) & 1) {
		lock = dib8000_read_word(state, 554); /* Viterbi Layer A */
		if (lock & 0x01)
			*stat |= FE_HAS_VITERBI;

		lock = dib8000_read_word(state, 555); /* Viterbi Layer B */
		if (lock & 0x01)
			*stat |= FE_HAS_VITERBI;

		lock = dib8000_read_word(state, 556); /* Viterbi Layer C */
		if (lock & 0x01)
			*stat |= FE_HAS_VITERBI;
	}

	return 0;
}