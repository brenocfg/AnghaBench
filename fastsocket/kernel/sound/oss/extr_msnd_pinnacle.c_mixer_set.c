#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* left_levels; int* right_levels; scalar_t__ SMA; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HDEXAR_AUX_SET_POTS ; 
 int /*<<< orphan*/  HDEXAR_IN_SET_POTS ; 
 int /*<<< orphan*/  HDEXAR_MIC_SET_POTS ; 
 int /*<<< orphan*/  HDEX_AUX_REQ ; 
 scalar_t__ SMA_bInPotPosLeft ; 
 scalar_t__ SMA_bInPotPosRight ; 
 scalar_t__ SMA_bMicPotPosLeft ; 
 scalar_t__ SMA_bMicPotPosRight ; 
 scalar_t__ SMA_wCurrMastVolLeft ; 
 scalar_t__ SMA_wCurrMastVolRight ; 
#define  SOUND_MIXER_IMIX 134 
#define  SOUND_MIXER_LINE 133 
#define  SOUND_MIXER_LINE1 132 
#define  SOUND_MIXER_MIC 131 
#define  SOUND_MIXER_PCM 130 
#define  SOUND_MIXER_SYNTH 129 
#define  SOUND_MIXER_VOLUME 128 
 int /*<<< orphan*/  bAuxPotPos ; 
 int /*<<< orphan*/  chk_send_dsp_cmd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ dev ; 
 int mixer_get (int) ; 
 int /*<<< orphan*/  msnd_send_word (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_potm (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_volm (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wCurrInVol ; 
 int /*<<< orphan*/  wCurrMHdrVol ; 
 int /*<<< orphan*/  wCurrPlayVol ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int mixer_set(int d, int value)
{
	int left = value & 0x000000ff;
	int right = (value & 0x0000ff00) >> 8;
	int bLeft, bRight;
	int wLeft, wRight;
	int updatemaster = 0;

	if (d > 31)
		return -EINVAL;

	bLeft = left * 0xff / 100;
	wLeft = left * 0xffff / 100;

	bRight = right * 0xff / 100;
	wRight = right * 0xffff / 100;

	dev.left_levels[d] = wLeft;
	dev.right_levels[d] = wRight;

	switch (d) {
		/* master volume unscaled controls */
	case SOUND_MIXER_LINE:			/* line pot control */
		/* scaled by IMIX in digital mix */
		writeb(bLeft, dev.SMA + SMA_bInPotPosLeft);
		writeb(bRight, dev.SMA + SMA_bInPotPosRight);
		if (msnd_send_word(&dev, 0, 0, HDEXAR_IN_SET_POTS) == 0)
			chk_send_dsp_cmd(&dev, HDEX_AUX_REQ);
		break;
#ifndef MSND_CLASSIC
	case SOUND_MIXER_MIC:			/* mic pot control */
		/* scaled by IMIX in digital mix */
		writeb(bLeft, dev.SMA + SMA_bMicPotPosLeft);
		writeb(bRight, dev.SMA + SMA_bMicPotPosRight);
		if (msnd_send_word(&dev, 0, 0, HDEXAR_MIC_SET_POTS) == 0)
			chk_send_dsp_cmd(&dev, HDEX_AUX_REQ);
		break;
#endif
	case SOUND_MIXER_VOLUME:		/* master volume */
		writew(wLeft, dev.SMA + SMA_wCurrMastVolLeft);
		writew(wRight, dev.SMA + SMA_wCurrMastVolRight);
		/* fall through */

	case SOUND_MIXER_LINE1:			/* aux pot control */
		/* scaled by master volume */
		/* fall through */

		/* digital controls */
	case SOUND_MIXER_SYNTH:			/* synth vol (dsp mix) */
	case SOUND_MIXER_PCM:			/* pcm vol (dsp mix) */
	case SOUND_MIXER_IMIX:			/* input monitor (dsp mix) */
		/* scaled by master volume */
		updatemaster = 1;
		break;

	default:
		return 0;
	}

	if (updatemaster) {
		/* update master volume scaled controls */
		update_volm(SOUND_MIXER_PCM, wCurrPlayVol);
		update_volm(SOUND_MIXER_IMIX, wCurrInVol);
#ifndef MSND_CLASSIC
		update_volm(SOUND_MIXER_SYNTH, wCurrMHdrVol);
#endif
		update_potm(SOUND_MIXER_LINE1, bAuxPotPos, HDEXAR_AUX_SET_POTS);
	}

	return mixer_get(d);
}