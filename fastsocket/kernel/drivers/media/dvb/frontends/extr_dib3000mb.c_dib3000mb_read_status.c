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
struct dvb_frontend {struct dib3000_state* demodulator_priv; } ;
struct dib3000_state {int dummy; } ;
typedef  int fe_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIB3000MB_REG_AGC_LOCK ; 
 int /*<<< orphan*/  DIB3000MB_REG_CARRIER_LOCK ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_CELL_ID ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_CODE_RATE_HP ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_CODE_RATE_LP ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_FFT ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_GUARD_TIME ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_HRCH ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_LOCK ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_QAM ; 
 int /*<<< orphan*/  DIB3000MB_REG_TPS_VIT_ALPHA ; 
 int /*<<< orphan*/  DIB3000MB_REG_TS_SYNC_LOCK ; 
 int /*<<< orphan*/  DIB3000MB_REG_VIT_LCK ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  deb_getf (char*,int,...) ; 
 int rd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib3000mb_read_status(struct dvb_frontend* fe, fe_status_t *stat)
{
	struct dib3000_state* state = fe->demodulator_priv;

	*stat = 0;

	if (rd(DIB3000MB_REG_AGC_LOCK))
		*stat |= FE_HAS_SIGNAL;
	if (rd(DIB3000MB_REG_CARRIER_LOCK))
		*stat |= FE_HAS_CARRIER;
	if (rd(DIB3000MB_REG_VIT_LCK))
		*stat |= FE_HAS_VITERBI;
	if (rd(DIB3000MB_REG_TS_SYNC_LOCK))
		*stat |= (FE_HAS_SYNC | FE_HAS_LOCK);

	deb_getf("actual status is %2x\n",*stat);

	deb_getf("autoval: tps: %d, qam: %d, hrch: %d, alpha: %d, hp: %d, lp: %d, guard: %d, fft: %d cell: %d\n",
			rd(DIB3000MB_REG_TPS_LOCK),
			rd(DIB3000MB_REG_TPS_QAM),
			rd(DIB3000MB_REG_TPS_HRCH),
			rd(DIB3000MB_REG_TPS_VIT_ALPHA),
			rd(DIB3000MB_REG_TPS_CODE_RATE_HP),
			rd(DIB3000MB_REG_TPS_CODE_RATE_LP),
			rd(DIB3000MB_REG_TPS_GUARD_TIME),
			rd(DIB3000MB_REG_TPS_FFT),
			rd(DIB3000MB_REG_TPS_CELL_ID));

	//*stat = FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	return 0;
}