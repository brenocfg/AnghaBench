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
typedef  int /*<<< orphan*/  u32 ;
struct tda18271_std_map_item {int /*<<< orphan*/  std; int /*<<< orphan*/  agc_mode; int /*<<< orphan*/  if_freq; } ;
struct tda18271_priv {int id; int /*<<< orphan*/  lock; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
#define  TDA18271HDC1 129 
#define  TDA18271HDC2 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tda18271_agc (struct dvb_frontend*) ; 
 int tda18271_channel_configuration (struct dvb_frontend*,struct tda18271_std_map_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tda18271_init (struct dvb_frontend*) ; 
 int /*<<< orphan*/  tda18271c1_rf_tracking_filter_calibration (struct dvb_frontend*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda18271c2_rf_tracking_filters_correction (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tda_fail (int) ; 
 int /*<<< orphan*/  tda_warn (char*) ; 

__attribute__((used)) static int tda18271_tune(struct dvb_frontend *fe,
			 struct tda18271_std_map_item *map, u32 freq, u32 bw)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	int ret;

	tda_dbg("freq = %d, ifc = %d, bw = %d, agc_mode = %d, std = %d\n",
		freq, map->if_freq, bw, map->agc_mode, map->std);

	ret = tda18271_agc(fe);
	if (tda_fail(ret))
		tda_warn("failed to configure agc\n");

	ret = tda18271_init(fe);
	if (tda_fail(ret))
		goto fail;

	mutex_lock(&priv->lock);

	switch (priv->id) {
	case TDA18271HDC1:
		tda18271c1_rf_tracking_filter_calibration(fe, freq, bw);
		break;
	case TDA18271HDC2:
		tda18271c2_rf_tracking_filters_correction(fe, freq);
		break;
	}
	ret = tda18271_channel_configuration(fe, map, freq, bw);

	mutex_unlock(&priv->lock);
fail:
	return ret;
}