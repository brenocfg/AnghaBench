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
struct TYPE_2__ {int xtal_freq; scalar_t__ pllref; scalar_t__ deemph_75; scalar_t__ japan_band; scalar_t__ soft_mute; scalar_t__ st_noise; scalar_t__ high_cut; scalar_t__ port2; scalar_t__ port1; } ;
struct tea5767_priv {unsigned int frequency; int /*<<< orphan*/  i2c_props; TYPE_1__ ctrl; } ;
struct dvb_frontend {struct tea5767_priv* tuner_priv; } ;
struct analog_parameters {unsigned int frequency; scalar_t__ audmode; } ;

/* Variables and functions */
 unsigned char TEA5767_DEEMPH_75 ; 
 unsigned char TEA5767_HIGH_CUT_CTRL ; 
#define  TEA5767_HIGH_LO_13MHz 131 
#define  TEA5767_HIGH_LO_32768 130 
 unsigned char TEA5767_HIGH_LO_INJECT ; 
 unsigned char TEA5767_JAPAN_BAND ; 
#define  TEA5767_LOW_LO_13MHz 129 
#define  TEA5767_LOW_LO_32768 128 
 unsigned char TEA5767_MONO ; 
 unsigned char TEA5767_PLLREF_ENABLE ; 
 unsigned char TEA5767_PORT1_HIGH ; 
 unsigned char TEA5767_PORT2_HIGH ; 
 unsigned char TEA5767_SOFT_MUTE ; 
 unsigned char TEA5767_ST_NOISE_CTL ; 
 unsigned char TEA5767_XTAL_32768 ; 
 scalar_t__ V4L2_TUNER_MODE_MONO ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  tea5767_status_dump (struct tea5767_priv*,unsigned char*) ; 
 int /*<<< orphan*/  tuner_dbg (char*,...) ; 
 int tuner_i2c_xfer_recv (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int tuner_i2c_xfer_send (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  tuner_warn (char*,int) ; 

__attribute__((used)) static int set_radio_freq(struct dvb_frontend *fe,
			  struct analog_parameters *params)
{
	struct tea5767_priv *priv = fe->tuner_priv;
	unsigned int frq = params->frequency;
	unsigned char buffer[5];
	unsigned div;
	int rc;

	tuner_dbg("radio freq = %d.%03d MHz\n", frq/16000,(frq/16)%1000);

	buffer[2] = 0;

	if (priv->ctrl.port1)
		buffer[2] |= TEA5767_PORT1_HIGH;

	if (params->audmode == V4L2_TUNER_MODE_MONO) {
		tuner_dbg("TEA5767 set to mono\n");
		buffer[2] |= TEA5767_MONO;
	} else {
		tuner_dbg("TEA5767 set to stereo\n");
	}


	buffer[3] = 0;

	if (priv->ctrl.port2)
		buffer[3] |= TEA5767_PORT2_HIGH;

	if (priv->ctrl.high_cut)
		buffer[3] |= TEA5767_HIGH_CUT_CTRL;

	if (priv->ctrl.st_noise)
		buffer[3] |= TEA5767_ST_NOISE_CTL;

	if (priv->ctrl.soft_mute)
		buffer[3] |= TEA5767_SOFT_MUTE;

	if (priv->ctrl.japan_band)
		buffer[3] |= TEA5767_JAPAN_BAND;

	buffer[4] = 0;

	if (priv->ctrl.deemph_75)
		buffer[4] |= TEA5767_DEEMPH_75;

	if (priv->ctrl.pllref)
		buffer[4] |= TEA5767_PLLREF_ENABLE;


	/* Rounds freq to next decimal value - for 62.5 KHz step */
	/* frq = 20*(frq/16)+radio_frq[frq%16]; */

	switch (priv->ctrl.xtal_freq) {
	case TEA5767_HIGH_LO_13MHz:
		tuner_dbg("radio HIGH LO inject xtal @ 13 MHz\n");
		buffer[2] |= TEA5767_HIGH_LO_INJECT;
		div = (frq * (4000 / 16) + 700000 + 225000 + 25000) / 50000;
		break;
	case TEA5767_LOW_LO_13MHz:
		tuner_dbg("radio LOW LO inject xtal @ 13 MHz\n");

		div = (frq * (4000 / 16) - 700000 - 225000 + 25000) / 50000;
		break;
	case TEA5767_LOW_LO_32768:
		tuner_dbg("radio LOW LO inject xtal @ 32,768 MHz\n");
		buffer[3] |= TEA5767_XTAL_32768;
		/* const 700=4000*175 Khz - to adjust freq to right value */
		div = ((frq * (4000 / 16) - 700000 - 225000) + 16384) >> 15;
		break;
	case TEA5767_HIGH_LO_32768:
	default:
		tuner_dbg("radio HIGH LO inject xtal @ 32,768 MHz\n");

		buffer[2] |= TEA5767_HIGH_LO_INJECT;
		buffer[3] |= TEA5767_XTAL_32768;
		div = ((frq * (4000 / 16) + 700000 + 225000) + 16384) >> 15;
		break;
	}
	buffer[0] = (div >> 8) & 0x3f;
	buffer[1] = div & 0xff;

	if (5 != (rc = tuner_i2c_xfer_send(&priv->i2c_props, buffer, 5)))
		tuner_warn("i2c i/o error: rc == %d (should be 5)\n", rc);

	if (debug) {
		if (5 != (rc = tuner_i2c_xfer_recv(&priv->i2c_props, buffer, 5)))
			tuner_warn("i2c i/o error: rc == %d (should be 5)\n", rc);
		else
			tea5767_status_dump(priv, buffer);
	}

	priv->frequency = frq * 125 / 2;

	return 0;
}