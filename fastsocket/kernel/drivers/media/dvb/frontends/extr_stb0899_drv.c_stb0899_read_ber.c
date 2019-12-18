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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct stb0899_internal {int /*<<< orphan*/  err_ctrl; int /*<<< orphan*/  lock; int /*<<< orphan*/  v_status; } ;
struct stb0899_state {int delsys; int /*<<< orphan*/  verbose; struct stb0899_internal internal; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  MAKEWORD16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOE ; 
 int /*<<< orphan*/  STB0899_ECNT1L ; 
 int /*<<< orphan*/  STB0899_ECNT1M ; 
 int STB0899_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SYS_DSS 130 
#define  SYS_DVBS 129 
#define  SYS_DVBS2 128 
 int /*<<< orphan*/  VSTATUS_PRFVIT ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stb0899_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct stb0899_state *state		= fe->demodulator_priv;
	struct stb0899_internal *internal	= &state->internal;

	u8  lsb, msb;
	u32 i;

	*ber = 0;

	switch (state->delsys) {
	case SYS_DVBS:
	case SYS_DSS:
		if (internal->lock) {
			/* average 5 BER values	*/
			for (i = 0; i < 5; i++) {
				msleep(100);
				lsb = stb0899_read_reg(state, STB0899_ECNT1L);
				msb = stb0899_read_reg(state, STB0899_ECNT1M);
				*ber += MAKEWORD16(msb, lsb);
			}
			*ber /= 5;
			/* Viterbi Check	*/
			if (STB0899_GETFIELD(VSTATUS_PRFVIT, internal->v_status)) {
				/* Error Rate		*/
				*ber *= 9766;
				/* ber = ber * 10 ^ 7	*/
				*ber /= (-1 + (1 << (2 * STB0899_GETFIELD(NOE, internal->err_ctrl))));
				*ber /= 8;
			}
		}
		break;
	case SYS_DVBS2:
		if (internal->lock) {
			/* Average 5 PER values	*/
			for (i = 0; i < 5; i++) {
				msleep(100);
				lsb = stb0899_read_reg(state, STB0899_ECNT1L);
				msb = stb0899_read_reg(state, STB0899_ECNT1M);
				*ber += MAKEWORD16(msb, lsb);
			}
			/* ber = ber * 10 ^ 7	*/
			*ber *= 10000000;
			*ber /= (-1 + (1 << (4 + 2 * STB0899_GETFIELD(NOE, internal->err_ctrl))));
		}
		break;
	default:
		dprintk(state->verbose, FE_DEBUG, 1, "Unsupported delivery system");
		return -EINVAL;
	}

	return 0;
}