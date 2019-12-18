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
typedef  unsigned char u8 ;
typedef  scalar_t__ u32 ;
struct tda18271_rf_tracking_filter_cal {int rf1_def; int rf2_def; int rf3_def; int rf_a1; int rf_b1; int rf_a2; int rf_b2; scalar_t__ rf3; scalar_t__ rf2; scalar_t__ rf1; } ;
struct tda18271_priv {unsigned char* tda18271_regs; struct tda18271_rf_tracking_filter_cal* rf_cal_state; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  RF1 130 
#define  RF2 129 
#define  RF3 128 
 size_t R_EB14 ; 
 int /*<<< orphan*/  tda18271_calc_rf_cal (struct dvb_frontend*,scalar_t__*) ; 
 unsigned char tda18271_calibrate_rf (struct dvb_frontend*,scalar_t__) ; 
 int tda18271_lookup_rf_band (struct dvb_frontend*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int tda18271_powerscan (struct dvb_frontend*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  tda_cal (char*,scalar_t__,int) ; 
 scalar_t__ tda_fail (int) ; 

__attribute__((used)) static int tda18271_rf_tracking_filters_init(struct dvb_frontend *fe, u32 freq)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	struct tda18271_rf_tracking_filter_cal *map = priv->rf_cal_state;
	unsigned char *regs = priv->tda18271_regs;
	int bcal, rf, i;
	s32 divisor, dividend;
#define RF1 0
#define RF2 1
#define RF3 2
	u32 rf_default[3];
	u32 rf_freq[3];
	u8 prog_cal[3];
	u8 prog_tab[3];

	i = tda18271_lookup_rf_band(fe, &freq, NULL);

	if (tda_fail(i))
		return i;

	rf_default[RF1] = 1000 * map[i].rf1_def;
	rf_default[RF2] = 1000 * map[i].rf2_def;
	rf_default[RF3] = 1000 * map[i].rf3_def;

	for (rf = RF1; rf <= RF3; rf++) {
		if (0 == rf_default[rf])
			return 0;
		tda_cal("freq = %d, rf = %d\n", freq, rf);

		/* look for optimized calibration frequency */
		bcal = tda18271_powerscan(fe, &rf_default[rf], &rf_freq[rf]);
		if (tda_fail(bcal))
			return bcal;

		tda18271_calc_rf_cal(fe, &rf_freq[rf]);
		prog_tab[rf] = regs[R_EB14];

		if (1 == bcal)
			prog_cal[rf] = tda18271_calibrate_rf(fe, rf_freq[rf]);
		else
			prog_cal[rf] = prog_tab[rf];

		switch (rf) {
		case RF1:
			map[i].rf_a1 = 0;
			map[i].rf_b1 = (s32)(prog_cal[RF1] - prog_tab[RF1]);
			map[i].rf1   = rf_freq[RF1] / 1000;
			break;
		case RF2:
			dividend = (s32)(prog_cal[RF2] - prog_tab[RF2]) -
				   (s32)(prog_cal[RF1] + prog_tab[RF1]);
			divisor = (s32)(rf_freq[RF2] - rf_freq[RF1]) / 1000;
			map[i].rf_a1 = (dividend / divisor);
			map[i].rf2   = rf_freq[RF2] / 1000;
			break;
		case RF3:
			dividend = (s32)(prog_cal[RF3] - prog_tab[RF3]) -
				   (s32)(prog_cal[RF2] + prog_tab[RF2]);
			divisor = (s32)(rf_freq[RF3] - rf_freq[RF2]) / 1000;
			map[i].rf_a2 = (dividend / divisor);
			map[i].rf_b2 = (s32)(prog_cal[RF2] - prog_tab[RF2]);
			map[i].rf3   = rf_freq[RF3] / 1000;
			break;
		default:
			BUG();
		}
	}

	return 0;
}