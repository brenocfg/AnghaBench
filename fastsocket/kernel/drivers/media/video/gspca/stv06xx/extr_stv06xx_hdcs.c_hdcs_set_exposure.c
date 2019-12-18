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
struct sd {struct hdcs* sensor_priv; } ;
struct TYPE_2__ {int cto; int rs; int er; } ;
struct hdcs {int exp_cache; int psmp; int w; TYPE_1__ exp; } ;
struct gspca_dev {int dummy; } ;
typedef  int __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_V4L2 ; 
 int HDCS00_CONTROL ; 
 int HDCS00_SROWEXPH ; 
 int HDCS00_SROWEXPL ; 
 int HDCS20_CONTROL ; 
 int HDCS20_ERROR ; 
 int HDCS20_SROWEXP ; 
 int HDCS_ADC_START_SIG_DUR ; 
 int HDCS_CLK_FREQ_MHZ ; 
 int HDCS_ROWEXPH ; 
 int HDCS_ROWEXPL ; 
 int HDCS_STATUS ; 
 scalar_t__ IS_1020 (struct sd*) ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int stv06xx_write_sensor_bytes (struct sd*,int*,int) ; 

__attribute__((used)) static int hdcs_set_exposure(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct hdcs *hdcs = sd->sensor_priv;
	int rowexp, srowexp;
	int max_srowexp;
	/* Column time period */
	int ct;
	/* Column processing period */
	int cp;
	/* Row processing period */
	int rp;
	/* Minimum number of column timing periods
	   within the column processing period */
	int mnct;
	int cycles, err;
	u8 exp[14];

	val &= 0xff;
	hdcs->exp_cache = val;

	cycles = val * HDCS_CLK_FREQ_MHZ * 257;

	ct = hdcs->exp.cto + hdcs->psmp + (HDCS_ADC_START_SIG_DUR + 2);
	cp = hdcs->exp.cto + (hdcs->w * ct / 2);

	/* the cycles one row takes */
	rp = hdcs->exp.rs + cp;

	rowexp = cycles / rp;

	/* the remaining cycles */
	cycles -= rowexp * rp;

	/* calculate sub-row exposure */
	if (IS_1020(sd)) {
		/* see HDCS-1020 datasheet 3.5.6.4, p. 63 */
		srowexp = hdcs->w - (cycles + hdcs->exp.er + 13) / ct;

		mnct = (hdcs->exp.er + 12 + ct - 1) / ct;
		max_srowexp = hdcs->w - mnct;
	} else {
		/* see HDCS-1000 datasheet 3.4.5.5, p. 61 */
		srowexp = cp - hdcs->exp.er - 6 - cycles;

		mnct = (hdcs->exp.er + 5 + ct - 1) / ct;
		max_srowexp = cp - mnct * ct - 1;
	}

	if (srowexp < 0)
		srowexp = 0;
	else if (srowexp > max_srowexp)
		srowexp = max_srowexp;

	if (IS_1020(sd)) {
		exp[0] = HDCS20_CONTROL;
		exp[1] = 0x00;		/* Stop streaming */
		exp[2] = HDCS_ROWEXPL;
		exp[3] = rowexp & 0xff;
		exp[4] = HDCS_ROWEXPH;
		exp[5] = rowexp >> 8;
		exp[6] = HDCS20_SROWEXP;
		exp[7] = (srowexp >> 2) & 0xff;
		exp[8] = HDCS20_ERROR;
		exp[9] = 0x10;		/* Clear exposure error flag*/
		exp[10] = HDCS20_CONTROL;
		exp[11] = 0x04;		/* Restart streaming */
		err = stv06xx_write_sensor_bytes(sd, exp, 6);
	} else {
		exp[0] = HDCS00_CONTROL;
		exp[1] = 0x00;         /* Stop streaming */
		exp[2] = HDCS_ROWEXPL;
		exp[3] = rowexp & 0xff;
		exp[4] = HDCS_ROWEXPH;
		exp[5] = rowexp >> 8;
		exp[6] = HDCS00_SROWEXPL;
		exp[7] = srowexp & 0xff;
		exp[8] = HDCS00_SROWEXPH;
		exp[9] = srowexp >> 8;
		exp[10] = HDCS_STATUS;
		exp[11] = 0x10;         /* Clear exposure error flag*/
		exp[12] = HDCS00_CONTROL;
		exp[13] = 0x04;         /* Restart streaming */
		err = stv06xx_write_sensor_bytes(sd, exp, 7);
		if (err < 0)
			return err;
	}
	PDEBUG(D_V4L2, "Writing exposure %d, rowexp %d, srowexp %d",
	       val, rowexp, srowexp);
	return err;
}