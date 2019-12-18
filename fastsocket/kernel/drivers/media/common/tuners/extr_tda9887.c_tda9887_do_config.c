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
struct tda9887_priv {char* data; int config; int std; scalar_t__ mode; } ;
struct dvb_frontend {struct tda9887_priv* analog_demod_priv; } ;

/* Variables and functions */
 int TDA9887_AUTOMUTE ; 
#define  TDA9887_DEEMPHASIS_50 130 
#define  TDA9887_DEEMPHASIS_75 129 
 int TDA9887_DEEMPHASIS_MASK ; 
#define  TDA9887_DEEMPHASIS_NONE 128 
 int TDA9887_GAIN_NORMAL ; 
 int TDA9887_GATING_18 ; 
 int TDA9887_INTERCARRIER ; 
 int TDA9887_INTERCARRIER_NTSC ; 
 int TDA9887_PORT1_ACTIVE ; 
 int TDA9887_PORT1_INACTIVE ; 
 int TDA9887_PORT2_ACTIVE ; 
 int TDA9887_PORT2_INACTIVE ; 
 int TDA9887_QSS ; 
 int TDA9887_RIF_41_3 ; 
 int TDA9887_TOP_SET ; 
 int V4L2_STD_NTSC ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 char cAutoMuteFmActive ; 
 char cDeemphasis50 ; 
 char cDeemphasis75 ; 
 char cDeemphasisOFF ; 
 char cDeemphasisON ; 
 char cGating_36 ; 
 char cOutputPort1Inactive ; 
 char cOutputPort2Inactive ; 
 char cQSS ; 
 char cRadioIF_41_30 ; 
 char cTopMask ; 
 char cTunerGainLow ; 
 char cVideoIFMask ; 

__attribute__((used)) static int tda9887_do_config(struct dvb_frontend *fe)
{
	struct tda9887_priv *priv = fe->analog_demod_priv;
	char *buf = priv->data;

	if (priv->config & TDA9887_PORT1_ACTIVE)
		buf[1] &= ~cOutputPort1Inactive;
	if (priv->config & TDA9887_PORT1_INACTIVE)
		buf[1] |= cOutputPort1Inactive;
	if (priv->config & TDA9887_PORT2_ACTIVE)
		buf[1] &= ~cOutputPort2Inactive;
	if (priv->config & TDA9887_PORT2_INACTIVE)
		buf[1] |= cOutputPort2Inactive;

	if (priv->config & TDA9887_QSS)
		buf[1] |= cQSS;
	if (priv->config & TDA9887_INTERCARRIER)
		buf[1] &= ~cQSS;

	if (priv->config & TDA9887_AUTOMUTE)
		buf[1] |= cAutoMuteFmActive;
	if (priv->config & TDA9887_DEEMPHASIS_MASK) {
		buf[2] &= ~0x60;
		switch (priv->config & TDA9887_DEEMPHASIS_MASK) {
		case TDA9887_DEEMPHASIS_NONE:
			buf[2] |= cDeemphasisOFF;
			break;
		case TDA9887_DEEMPHASIS_50:
			buf[2] |= cDeemphasisON | cDeemphasis50;
			break;
		case TDA9887_DEEMPHASIS_75:
			buf[2] |= cDeemphasisON | cDeemphasis75;
			break;
		}
	}
	if (priv->config & TDA9887_TOP_SET) {
		buf[2] &= ~cTopMask;
		buf[2] |= (priv->config >> 8) & cTopMask;
	}
	if ((priv->config & TDA9887_INTERCARRIER_NTSC) &&
	    (priv->std & V4L2_STD_NTSC))
		buf[1] &= ~cQSS;
	if (priv->config & TDA9887_GATING_18)
		buf[3] &= ~cGating_36;

	if (priv->mode == V4L2_TUNER_RADIO) {
		if (priv->config & TDA9887_RIF_41_3) {
			buf[3] &= ~cVideoIFMask;
			buf[3] |= cRadioIF_41_30;
		}
		if (priv->config & TDA9887_GAIN_NORMAL)
			buf[3] &= ~cTunerGainLow;
	}

	return 0;
}