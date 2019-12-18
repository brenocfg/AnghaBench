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
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int* bytes; } ;
struct CHIPSTATE {int /*<<< orphan*/  mode; TYPE_1__ shadow; struct v4l2_subdev sd; } ;

/* Variables and functions */
 int MAXREGS ; 
 int /*<<< orphan*/  TDA9874A_AOSR ; 
 int /*<<< orphan*/  TDA9874A_FMMR ; 
 int /*<<< orphan*/  TDA9874A_MDACOSR ; 
 int /*<<< orphan*/  TDA9874A_NCONR ; 
#define  V4L2_TUNER_MODE_LANG1 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int /*<<< orphan*/  chip_write (struct CHIPSTATE*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debug ; 
 int tda9874a_ESP ; 
 int tda9874a_NCONR ; 
 int tda9874a_dic ; 
 scalar_t__ tda9874a_mode ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int,int,int) ; 

__attribute__((used)) static void tda9874a_setmode(struct CHIPSTATE *chip, int mode)
{
	struct v4l2_subdev *sd = &chip->sd;

	/* Disable/enable NICAM auto-muting (based on DSR.RSSF status bit). */
	/* If auto-muting is disabled, we can hear a signal of degrading quality. */
	if (tda9874a_mode) {
		if(chip->shadow.bytes[MAXREGS-2] & 0x20) /* DSR.RSSF=1 */
			tda9874a_NCONR &= 0xfe; /* enable */
		else
			tda9874a_NCONR |= 0x01; /* disable */
		chip_write(chip, TDA9874A_NCONR, tda9874a_NCONR);
	}

	/* Note: TDA9874A supports automatic FM dematrixing (FMMR register)
	 * and has auto-select function for audio output (AOSR register).
	 * Old TDA9874H doesn't support these features.
	 * TDA9874A also has additional mono output pin (OUTM), which
	 * on same (all?) tv-cards is not used, anyway (as well as MONOIN).
	 */
	if(tda9874a_dic == 0x11) {
		int aosr = 0x80;
		int mdacosr = (tda9874a_mode) ? 0x82:0x80;

		switch(mode) {
		case V4L2_TUNER_MODE_MONO:
		case V4L2_TUNER_MODE_STEREO:
			break;
		case V4L2_TUNER_MODE_LANG1:
			aosr = 0x80; /* auto-select, dual A/A */
			mdacosr = (tda9874a_mode) ? 0x82:0x80;
			break;
		case V4L2_TUNER_MODE_LANG2:
			aosr = 0xa0; /* auto-select, dual B/B */
			mdacosr = (tda9874a_mode) ? 0x83:0x81;
			break;
		default:
			chip->mode = 0;
			return;
		}
		chip_write(chip, TDA9874A_AOSR, aosr);
		chip_write(chip, TDA9874A_MDACOSR, mdacosr);

		v4l2_dbg(1, debug, sd, "tda9874a_setmode(): req. mode %d; AOSR=0x%X, MDACOSR=0x%X.\n",
			mode, aosr, mdacosr);

	} else { /* dic == 0x07 */
		int fmmr,aosr;

		switch(mode) {
		case V4L2_TUNER_MODE_MONO:
			fmmr = 0x00; /* mono */
			aosr = 0x10; /* A/A */
			break;
		case V4L2_TUNER_MODE_STEREO:
			if(tda9874a_mode) {
				fmmr = 0x00;
				aosr = 0x00; /* handled by NICAM auto-mute */
			} else {
				fmmr = (tda9874a_ESP == 1) ? 0x05 : 0x04; /* stereo */
				aosr = 0x00;
			}
			break;
		case V4L2_TUNER_MODE_LANG1:
			fmmr = 0x02; /* dual */
			aosr = 0x10; /* dual A/A */
			break;
		case V4L2_TUNER_MODE_LANG2:
			fmmr = 0x02; /* dual */
			aosr = 0x20; /* dual B/B */
			break;
		default:
			chip->mode = 0;
			return;
		}
		chip_write(chip, TDA9874A_FMMR, fmmr);
		chip_write(chip, TDA9874A_AOSR, aosr);

		v4l2_dbg(1, debug, sd, "tda9874a_setmode(): req. mode %d; FMMR=0x%X, AOSR=0x%X.\n",
			mode, fmmr, aosr);
	}
}