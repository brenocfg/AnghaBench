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
struct nxt6000_state {TYPE_1__* config; } ;
struct dvb_frontend {struct nxt6000_state* demodulator_priv; } ;
struct TYPE_2__ {scalar_t__ clock_inversion; } ;

/* Variables and functions */
 int AGCLAST ; 
 int /*<<< orphan*/  ANALOG_CONTROL_0 ; 
 int /*<<< orphan*/  BER_CTRL ; 
 int /*<<< orphan*/  CAS_FREQ ; 
 int CLKINVERSION ; 
 int /*<<< orphan*/  DIAG_CONFIG ; 
 int /*<<< orphan*/  EN_DMD_RACQ ; 
 int FORCEMODE8K ; 
 int INITIAL_AGC_BW ; 
 int /*<<< orphan*/  OFDM_AGC_CTL ; 
 int /*<<< orphan*/  OFDM_CAS_CTL ; 
 int /*<<< orphan*/  OFDM_COR_CTL ; 
 int /*<<< orphan*/  OFDM_COR_MODEGUARD ; 
 int /*<<< orphan*/  OFDM_ITB_FREQ_1 ; 
 int /*<<< orphan*/  OFDM_ITB_FREQ_2 ; 
 int /*<<< orphan*/  OFDM_PPM_CTL_1 ; 
 int /*<<< orphan*/  OFDM_SYR_CTL ; 
 int /*<<< orphan*/  OFDM_TRL_NOMINALRATE_1 ; 
 int /*<<< orphan*/  OFDM_TRL_NOMINALRATE_2 ; 
 int PPM256 ; 
 int /*<<< orphan*/  RS_COR_SYNC_PARAM ; 
 int /*<<< orphan*/  SUB_DIAG_MODE_SEL ; 
 int SYNC_PARAM ; 
 int TB_SET ; 
 int /*<<< orphan*/  TS_FORMAT ; 
 int /*<<< orphan*/  VIT_BERTIME_0 ; 
 int /*<<< orphan*/  VIT_BERTIME_1 ; 
 int /*<<< orphan*/  VIT_BERTIME_2 ; 
 int /*<<< orphan*/  VIT_COR_CTL ; 
 int /*<<< orphan*/  VIT_COR_INTEN ; 
 int VIT_COR_RESYNC ; 
 int nxt6000_readreg (struct nxt6000_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nxt6000_writereg (struct nxt6000_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nxt6000_setup(struct dvb_frontend* fe)
{
	struct nxt6000_state* state = fe->demodulator_priv;

	nxt6000_writereg(state, RS_COR_SYNC_PARAM, SYNC_PARAM);
	nxt6000_writereg(state, BER_CTRL, /*(1 << 2) | */ (0x01 << 1) | 0x01);
	nxt6000_writereg(state, VIT_BERTIME_2, 0x00);  // BER Timer = 0x000200 * 256 = 131072 bits
	nxt6000_writereg(state, VIT_BERTIME_1, 0x02);  //
	nxt6000_writereg(state, VIT_BERTIME_0, 0x00);  //
	nxt6000_writereg(state, VIT_COR_INTEN, 0x98); // Enable BER interrupts
	nxt6000_writereg(state, VIT_COR_CTL, 0x82);   // Enable BER measurement
	nxt6000_writereg(state, VIT_COR_CTL, VIT_COR_RESYNC | 0x02 );
	nxt6000_writereg(state, OFDM_COR_CTL, (0x01 << 5) | (nxt6000_readreg(state, OFDM_COR_CTL) & 0x0F));
	nxt6000_writereg(state, OFDM_COR_MODEGUARD, FORCEMODE8K | 0x02);
	nxt6000_writereg(state, OFDM_AGC_CTL, AGCLAST | INITIAL_AGC_BW);
	nxt6000_writereg(state, OFDM_ITB_FREQ_1, 0x06);
	nxt6000_writereg(state, OFDM_ITB_FREQ_2, 0x31);
	nxt6000_writereg(state, OFDM_CAS_CTL, (0x01 << 7) | (0x02 << 3) | 0x04);
	nxt6000_writereg(state, CAS_FREQ, 0xBB);	/* CHECKME */
	nxt6000_writereg(state, OFDM_SYR_CTL, 1 << 2);
	nxt6000_writereg(state, OFDM_PPM_CTL_1, PPM256);
	nxt6000_writereg(state, OFDM_TRL_NOMINALRATE_1, 0x49);
	nxt6000_writereg(state, OFDM_TRL_NOMINALRATE_2, 0x72);
	nxt6000_writereg(state, ANALOG_CONTROL_0, 1 << 5);
	nxt6000_writereg(state, EN_DMD_RACQ, (1 << 7) | (3 << 4) | 2);
	nxt6000_writereg(state, DIAG_CONFIG, TB_SET);

	if (state->config->clock_inversion)
		nxt6000_writereg(state, SUB_DIAG_MODE_SEL, CLKINVERSION);
	else
		nxt6000_writereg(state, SUB_DIAG_MODE_SEL, 0);

	nxt6000_writereg(state, TS_FORMAT, 0);
}