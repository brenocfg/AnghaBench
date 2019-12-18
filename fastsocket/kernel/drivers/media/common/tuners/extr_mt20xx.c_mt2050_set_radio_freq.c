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
struct microtune_priv {int dummy; } ;
struct dvb_frontend {struct microtune_priv* tuner_priv; } ;
struct analog_parameters {int std; int frequency; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  mt2050_set_antenna (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt2050_set_if_freq (struct dvb_frontend*,int,int) ; 
 int /*<<< orphan*/  radio_antenna ; 
 int /*<<< orphan*/  tuner_dbg (char*) ; 

__attribute__((used)) static int mt2050_set_radio_freq(struct dvb_frontend *fe,
				 struct analog_parameters *params)
{
	struct microtune_priv *priv = fe->tuner_priv;
	int if2;

	if (params->std & V4L2_STD_525_60) {
		tuner_dbg("pinnacle ntsc\n");
		if2 = 41300 * 1000;
	} else {
		tuner_dbg("pinnacle pal\n");
		if2 = 33300 * 1000;
	}

	mt2050_set_if_freq(fe, params->frequency * 125 / 2, if2);
	mt2050_set_antenna(fe, radio_antenna);

	return 0;
}