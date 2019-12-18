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
struct tda8290_priv {int tda8290_easy_mode; int ver; } ;
struct dvb_frontend {struct tda8290_priv* analog_demod_priv; } ;
struct analog_parameters {int std; scalar_t__ mode; } ;

/* Variables and functions */
 int TDA8295 ; 
 int V4L2_STD_B ; 
 int V4L2_STD_DK ; 
 int V4L2_STD_GH ; 
 int V4L2_STD_MN ; 
 int V4L2_STD_PAL_I ; 
 int V4L2_STD_SECAM_L ; 
 int V4L2_STD_SECAM_LC ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  tuner_dbg (char*,...) ; 

__attribute__((used)) static void set_audio(struct dvb_frontend *fe,
		      struct analog_parameters *params)
{
	struct tda8290_priv *priv = fe->analog_demod_priv;
	char* mode;

	if (params->std & V4L2_STD_MN) {
		priv->tda8290_easy_mode = 0x01;
		mode = "MN";
	} else if (params->std & V4L2_STD_B) {
		priv->tda8290_easy_mode = 0x02;
		mode = "B";
	} else if (params->std & V4L2_STD_GH) {
		priv->tda8290_easy_mode = 0x04;
		mode = "GH";
	} else if (params->std & V4L2_STD_PAL_I) {
		priv->tda8290_easy_mode = 0x08;
		mode = "I";
	} else if (params->std & V4L2_STD_DK) {
		priv->tda8290_easy_mode = 0x10;
		mode = "DK";
	} else if (params->std & V4L2_STD_SECAM_L) {
		priv->tda8290_easy_mode = 0x20;
		mode = "L";
	} else if (params->std & V4L2_STD_SECAM_LC) {
		priv->tda8290_easy_mode = 0x40;
		mode = "LC";
	} else {
		priv->tda8290_easy_mode = 0x10;
		mode = "xx";
	}

	if (params->mode == V4L2_TUNER_RADIO) {
		/* Set TDA8295 to FM radio; Start TDA8290 with MN values */
		priv->tda8290_easy_mode = (priv->ver & TDA8295) ? 0x80 : 0x01;
		tuner_dbg("setting to radio FM\n");
	} else {
		tuner_dbg("setting tda829x to system %s\n", mode);
	}
}