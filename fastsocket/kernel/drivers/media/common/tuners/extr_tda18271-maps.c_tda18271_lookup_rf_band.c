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
struct tda18271_rf_tracking_filter_cal {int rfmax; int /*<<< orphan*/  rfband; int /*<<< orphan*/  rf_b2; int /*<<< orphan*/  rf_b1; int /*<<< orphan*/  rf_a2; int /*<<< orphan*/  rf_a1; int /*<<< orphan*/  rf3; int /*<<< orphan*/  rf2; int /*<<< orphan*/  rf1; int /*<<< orphan*/  rf3_def; int /*<<< orphan*/  rf2_def; int /*<<< orphan*/  rf1_def; } ;
struct tda18271_priv {struct tda18271_rf_tracking_filter_cal* rf_cal_state; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 int DBG_ADV ; 
 int EINVAL ; 
 int tda18271_debug ; 
 int /*<<< orphan*/  tda_map (char*,int,int,...) ; 

int tda18271_lookup_rf_band(struct dvb_frontend *fe, u32 *freq, u8 *rf_band)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	struct tda18271_rf_tracking_filter_cal *map = priv->rf_cal_state;
	int i = 0;

	while ((map[i].rfmax * 1000) < *freq) {
		if (tda18271_debug & DBG_ADV)
			tda_map("(%d) rfmax = %d < freq = %d, "
				"rf1_def = %d, rf2_def = %d, rf3_def = %d, "
				"rf1 = %d, rf2 = %d, rf3 = %d, "
				"rf_a1 = %d, rf_a2 = %d, "
				"rf_b1 = %d, rf_b2 = %d\n",
				i, map[i].rfmax * 1000, *freq,
				map[i].rf1_def, map[i].rf2_def, map[i].rf3_def,
				map[i].rf1, map[i].rf2, map[i].rf3,
				map[i].rf_a1, map[i].rf_a2,
				map[i].rf_b1, map[i].rf_b2);
		if (map[i].rfmax == 0)
			return -EINVAL;
		i++;
	}
	if (rf_band)
		*rf_band = map[i].rfband;

	tda_map("(%d) rf_band = %02x\n", i, map[i].rfband);

	return i;
}