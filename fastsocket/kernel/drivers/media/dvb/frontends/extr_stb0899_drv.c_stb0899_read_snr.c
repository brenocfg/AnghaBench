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
typedef  int /*<<< orphan*/  u32 ;
typedef  unsigned int u16 ;
struct stb0899_internal {int /*<<< orphan*/  lock; } ;
struct stb0899_state {int delsys; int /*<<< orphan*/  verbose; struct stb0899_internal internal; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ESN0_EST ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 unsigned int MAKEWORD16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int STB0899_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_NIRM ; 
 int /*<<< orphan*/  STB0899_READ_S2REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_S2DEMOD ; 
 int /*<<< orphan*/  STB0899_VSTATUS ; 
#define  SYS_DSS 130 
#define  SYS_DVBS 129 
#define  SYS_DVBS2 128 
 int /*<<< orphan*/  UWP_CNTRL1 ; 
 int /*<<< orphan*/  UWP_ESN0_QUANT ; 
 int /*<<< orphan*/  UWP_STAT2 ; 
 int /*<<< orphan*/  VSTATUS_LOCKEDVIT ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  stb0899_cn_tab ; 
 int /*<<< orphan*/  stb0899_est_tab ; 
 int /*<<< orphan*/  stb0899_quant_tab ; 
 int /*<<< orphan*/  stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb0899_read_regs (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* stb0899_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int stb0899_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct stb0899_state *state		= fe->demodulator_priv;
	struct stb0899_internal *internal	= &state->internal;

	unsigned int val, quant, quantn = -1, est, estn = -1;
	u8 buf[2];
	u32 reg;

	reg  = stb0899_read_reg(state, STB0899_VSTATUS);
	switch (state->delsys) {
	case SYS_DVBS:
	case SYS_DSS:
		if (internal->lock) {
			if (STB0899_GETFIELD(VSTATUS_LOCKEDVIT, reg)) {

				stb0899_read_regs(state, STB0899_NIRM, buf, 2);
				val = MAKEWORD16(buf[0], buf[1]);

				*snr = stb0899_table_lookup(stb0899_cn_tab, ARRAY_SIZE(stb0899_cn_tab) - 1, val);
				dprintk(state->verbose, FE_DEBUG, 1, "NIR = 0x%02x%02x = %u, C/N = %d * 0.1 dBm\n",
					buf[0], buf[1], val, *snr);
			}
		}
		break;
	case SYS_DVBS2:
		if (internal->lock) {
			reg = STB0899_READ_S2REG(STB0899_S2DEMOD, UWP_CNTRL1);
			quant = STB0899_GETFIELD(UWP_ESN0_QUANT, reg);
			reg = STB0899_READ_S2REG(STB0899_S2DEMOD, UWP_STAT2);
			est = STB0899_GETFIELD(ESN0_EST, reg);
			if (est == 1)
				val = 301; /* C/N = 30.1 dB */
			else if (est == 2)
				val = 270; /* C/N = 27.0 dB */
			else {
				/* quantn = 100 * log(quant^2) */
				quantn = stb0899_table_lookup(stb0899_quant_tab, ARRAY_SIZE(stb0899_quant_tab) - 1, quant * 100);
				/* estn = 100 * log(est) */
				estn = stb0899_table_lookup(stb0899_est_tab, ARRAY_SIZE(stb0899_est_tab) - 1, est);
				/* snr(dBm/10) = -10*(log(est)-log(quant^2)) => snr(dBm/10) = (100*log(quant^2)-100*log(est))/10 */
				val = (quantn - estn) / 10;
			}
			*snr = val;
			dprintk(state->verbose, FE_DEBUG, 1, "Es/N0 quant = %d (%d) estimate = %u (%d), C/N = %d * 0.1 dBm",
				quant, quantn, est, estn, val);
		}
		break;
	default:
		dprintk(state->verbose, FE_DEBUG, 1, "Unsupported delivery system");
		return -EINVAL;
	}

	return 0;
}