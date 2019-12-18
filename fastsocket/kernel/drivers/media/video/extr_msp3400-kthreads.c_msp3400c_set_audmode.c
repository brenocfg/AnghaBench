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
struct msp_state {int audmode; scalar_t__ opmode; int mode; int rxsubchans; int /*<<< orphan*/  nicam_on; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSP_CARRIER (double) ; 
#define  MSP_MODE_AM_NICAM 140 
#define  MSP_MODE_BTSC 139 
#define  MSP_MODE_EXTERN 138 
#define  MSP_MODE_FM_NICAM1 137 
#define  MSP_MODE_FM_NICAM2 136 
#define  MSP_MODE_FM_RADIO 135 
#define  MSP_MODE_FM_SAT 134 
#define  MSP_MODE_FM_TERRA 133 
 scalar_t__ OPMODE_AUTOSELECT ; 
 int /*<<< orphan*/  SCART_MONO ; 
#define  V4L2_TUNER_MODE_LANG1 132 
#define  V4L2_TUNER_MODE_LANG1_LANG2 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int V4L2_TUNER_SUB_LANG2 ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  msp3400c_set_carrier (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msp_debug ; 
 int /*<<< orphan*/  msp_set_scart (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msp_set_source (struct i2c_client*,int) ; 
 int /*<<< orphan*/  msp_write_dsp (struct i2c_client*,int,int) ; 
 struct msp_state* to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,...) ; 

__attribute__((used)) static void msp3400c_set_audmode(struct i2c_client *client)
{
	static char *strmode[] = {
		"mono", "stereo", "lang2", "lang1", "lang1+lang2"
	};
	struct msp_state *state = to_state(i2c_get_clientdata(client));
	char *modestr = (state->audmode >= 0 && state->audmode < 5) ?
		strmode[state->audmode] : "unknown";
	int src = 0;	/* channel source: FM/AM, nicam or SCART */
	int audmode = state->audmode;

	if (state->opmode == OPMODE_AUTOSELECT) {
		/* this method would break everything, let's make sure
		 * it's never called
		 */
		v4l_dbg(1, msp_debug, client,
			"set_audmode called with mode=%d instead of set_source (ignored)\n",
			state->audmode);
		return;
	}

	/* Note: for the C and D revs no NTSC stereo + SAP is possible as
	   the hardware does not support SAP. So the rxsubchans combination
	   of STEREO | LANG2 does not occur. */

	if (state->mode != MSP_MODE_EXTERN) {
		/* switch to mono if only mono is available */
		if (state->rxsubchans == V4L2_TUNER_SUB_MONO)
			audmode = V4L2_TUNER_MODE_MONO;
		/* if bilingual */
		else if (state->rxsubchans & V4L2_TUNER_SUB_LANG2) {
			/* and mono or stereo, then fallback to lang1 */
			if (audmode == V4L2_TUNER_MODE_MONO ||
			    audmode == V4L2_TUNER_MODE_STEREO)
				audmode = V4L2_TUNER_MODE_LANG1;
		}
		/* if stereo, and audmode is not mono, then switch to stereo */
		else if (audmode != V4L2_TUNER_MODE_MONO)
			audmode = V4L2_TUNER_MODE_STEREO;
	}

	/* switch demodulator */
	switch (state->mode) {
	case MSP_MODE_FM_TERRA:
		v4l_dbg(1, msp_debug, client, "FM set_audmode: %s\n", modestr);
		switch (audmode) {
		case V4L2_TUNER_MODE_STEREO:
			msp_write_dsp(client, 0x000e, 0x3001);
			break;
		case V4L2_TUNER_MODE_MONO:
		case V4L2_TUNER_MODE_LANG1:
		case V4L2_TUNER_MODE_LANG2:
		case V4L2_TUNER_MODE_LANG1_LANG2:
			msp_write_dsp(client, 0x000e, 0x3000);
			break;
		}
		break;
	case MSP_MODE_FM_SAT:
		v4l_dbg(1, msp_debug, client, "SAT set_audmode: %s\n", modestr);
		switch (audmode) {
		case V4L2_TUNER_MODE_MONO:
			msp3400c_set_carrier(client, MSP_CARRIER(6.5), MSP_CARRIER(6.5));
			break;
		case V4L2_TUNER_MODE_STEREO:
		case V4L2_TUNER_MODE_LANG1_LANG2:
			msp3400c_set_carrier(client, MSP_CARRIER(7.2), MSP_CARRIER(7.02));
			break;
		case V4L2_TUNER_MODE_LANG1:
			msp3400c_set_carrier(client, MSP_CARRIER(7.38), MSP_CARRIER(7.02));
			break;
		case V4L2_TUNER_MODE_LANG2:
			msp3400c_set_carrier(client, MSP_CARRIER(7.38), MSP_CARRIER(7.02));
			break;
		}
		break;
	case MSP_MODE_FM_NICAM1:
	case MSP_MODE_FM_NICAM2:
	case MSP_MODE_AM_NICAM:
		v4l_dbg(1, msp_debug, client,
			"NICAM set_audmode: %s\n", modestr);
		if (state->nicam_on)
			src = 0x0100;  /* NICAM */
		break;
	case MSP_MODE_BTSC:
		v4l_dbg(1, msp_debug, client,
			"BTSC set_audmode: %s\n", modestr);
		break;
	case MSP_MODE_EXTERN:
		v4l_dbg(1, msp_debug, client,
			"extern set_audmode: %s\n", modestr);
		src = 0x0200;  /* SCART */
		break;
	case MSP_MODE_FM_RADIO:
		v4l_dbg(1, msp_debug, client,
			"FM-Radio set_audmode: %s\n", modestr);
		break;
	default:
		v4l_dbg(1, msp_debug, client, "mono set_audmode\n");
		return;
	}

	/* switch audio */
	v4l_dbg(1, msp_debug, client, "set audmode %d\n", audmode);
	switch (audmode) {
	case V4L2_TUNER_MODE_STEREO:
	case V4L2_TUNER_MODE_LANG1_LANG2:
		src |= 0x0020;
		break;
	case V4L2_TUNER_MODE_MONO:
		if (state->mode == MSP_MODE_AM_NICAM) {
			v4l_dbg(1, msp_debug, client, "switching to AM mono\n");
			/* AM mono decoding is handled by tuner, not MSP chip */
			/* SCART switching control register */
			msp_set_scart(client, SCART_MONO, 0);
			src = 0x0200;
			break;
		}
		if (state->rxsubchans & V4L2_TUNER_SUB_STEREO)
			src = 0x0030;
		break;
	case V4L2_TUNER_MODE_LANG1:
		break;
	case V4L2_TUNER_MODE_LANG2:
		src |= 0x0010;
		break;
	}
	v4l_dbg(1, msp_debug, client,
		"set_audmode final source/matrix = 0x%x\n", src);

	msp_set_source(client, src);
}