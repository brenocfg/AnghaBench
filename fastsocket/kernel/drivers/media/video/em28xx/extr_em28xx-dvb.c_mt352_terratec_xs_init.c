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
typedef  int /*<<< orphan*/  tuner_go ;
typedef  int /*<<< orphan*/  trl_nom_cfg ;
typedef  int /*<<< orphan*/  tps_given_cfg ;
struct dvb_frontend {int dummy; } ;
typedef  int /*<<< orphan*/  rs_err_cfg ;
typedef  int /*<<< orphan*/  reset ;
typedef  int /*<<< orphan*/  input_freq_cfg ;
typedef  int /*<<< orphan*/  clock_config ;
typedef  int /*<<< orphan*/  capt_range_cfg ;
typedef  int /*<<< orphan*/  agc_cfg ;
typedef  int /*<<< orphan*/  adc_ctl_1_cfg ;

/* Variables and functions */
#define  ADC_CTL_1 137 
#define  AGC_TARGET 136 
#define  CAPT_RANGE 135 
#define  CLOCK_CTL 134 
#define  INPUT_FREQ_1 133 
#define  RESET 132 
#define  RS_ERR_PER_1 131 
#define  TPS_GIVEN_1 130 
#define  TRL_NOMINAL_RATE_1 129 
#define  TUNER_GO 128 
 int /*<<< orphan*/  mt352_write (struct dvb_frontend*,int*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mt352_terratec_xs_init(struct dvb_frontend *fe)
{
	/* Values extracted from a USB trace of the Terratec Windows driver */
	static u8 clock_config[]   = { CLOCK_CTL,  0x38, 0x2c };
	static u8 reset[]          = { RESET,      0x80 };
	static u8 adc_ctl_1_cfg[]  = { ADC_CTL_1,  0x40 };
	static u8 agc_cfg[]        = { AGC_TARGET, 0x28, 0xa0 };
	static u8 input_freq_cfg[] = { INPUT_FREQ_1, 0x31, 0xb8 };
	static u8 rs_err_cfg[]     = { RS_ERR_PER_1, 0x00, 0x4d };
	static u8 capt_range_cfg[] = { CAPT_RANGE, 0x32 };
	static u8 trl_nom_cfg[]    = { TRL_NOMINAL_RATE_1, 0x64, 0x00 };
	static u8 tps_given_cfg[]  = { TPS_GIVEN_1, 0x40, 0x80, 0x50 };
	static u8 tuner_go[]       = { TUNER_GO, 0x01};

	mt352_write(fe, clock_config,   sizeof(clock_config));
	udelay(200);
	mt352_write(fe, reset,          sizeof(reset));
	mt352_write(fe, adc_ctl_1_cfg,  sizeof(adc_ctl_1_cfg));
	mt352_write(fe, agc_cfg,        sizeof(agc_cfg));
	mt352_write(fe, input_freq_cfg, sizeof(input_freq_cfg));
	mt352_write(fe, rs_err_cfg,     sizeof(rs_err_cfg));
	mt352_write(fe, capt_range_cfg, sizeof(capt_range_cfg));
	mt352_write(fe, trl_nom_cfg,    sizeof(trl_nom_cfg));
	mt352_write(fe, tps_given_cfg,  sizeof(tps_given_cfg));
	mt352_write(fe, tuner_go,       sizeof(tuner_go));
	return 0;
}