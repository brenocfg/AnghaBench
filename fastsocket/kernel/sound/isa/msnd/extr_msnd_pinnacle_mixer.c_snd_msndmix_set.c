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
struct snd_msnd {int* left_levels; int* right_levels; scalar_t__ type; scalar_t__ SMA; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HDEXAR_AUX_SET_POTS ; 
 int /*<<< orphan*/  HDEXAR_IN_SET_POTS ; 
 int /*<<< orphan*/  HDEXAR_MIC_SET_POTS ; 
 int /*<<< orphan*/  HDEX_AUX_REQ ; 
 int LEVEL_ENTRIES ; 
#define  MSND_MIXER_AUX 134 
#define  MSND_MIXER_IMIX 133 
#define  MSND_MIXER_LINE 132 
#define  MSND_MIXER_MIC 131 
#define  MSND_MIXER_PCM 130 
#define  MSND_MIXER_SYNTH 129 
#define  MSND_MIXER_VOLUME 128 
 scalar_t__ SMA_bInPotPosLeft ; 
 scalar_t__ SMA_bInPotPosRight ; 
 scalar_t__ SMA_bMicPotPosLeft ; 
 scalar_t__ SMA_bMicPotPosRight ; 
 scalar_t__ SMA_wCurrMastVolLeft ; 
 scalar_t__ SMA_wCurrMastVolRight ; 
 int /*<<< orphan*/  bAuxPotPos ; 
 scalar_t__ msndClassic ; 
 scalar_t__ msndPinnacle ; 
 int /*<<< orphan*/  snd_msnd_send_dsp_cmd (struct snd_msnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_msnd_send_word (struct snd_msnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_potm (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_volm (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wCurrInVol ; 
 int /*<<< orphan*/  wCurrMHdrVol ; 
 int /*<<< orphan*/  wCurrPlayVol ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int snd_msndmix_set(struct snd_msnd *dev, int d, int left, int right)
{
	int bLeft, bRight;
	int wLeft, wRight;
	int updatemaster = 0;

	if (d >= LEVEL_ENTRIES)
		return -EINVAL;

	bLeft = left * 0xff / 100;
	wLeft = left * 0xffff / 100;

	bRight = right * 0xff / 100;
	wRight = right * 0xffff / 100;

	dev->left_levels[d] = wLeft;
	dev->right_levels[d] = wRight;

	switch (d) {
		/* master volume unscaled controls */
	case MSND_MIXER_LINE:			/* line pot control */
		/* scaled by IMIX in digital mix */
		writeb(bLeft, dev->SMA + SMA_bInPotPosLeft);
		writeb(bRight, dev->SMA + SMA_bInPotPosRight);
		if (snd_msnd_send_word(dev, 0, 0, HDEXAR_IN_SET_POTS) == 0)
			snd_msnd_send_dsp_cmd(dev, HDEX_AUX_REQ);
		break;
	case MSND_MIXER_MIC:			/* mic pot control */
		if (dev->type == msndClassic)
			return -EINVAL;
		/* scaled by IMIX in digital mix */
		writeb(bLeft, dev->SMA + SMA_bMicPotPosLeft);
		writeb(bRight, dev->SMA + SMA_bMicPotPosRight);
		if (snd_msnd_send_word(dev, 0, 0, HDEXAR_MIC_SET_POTS) == 0)
			snd_msnd_send_dsp_cmd(dev, HDEX_AUX_REQ);
		break;
	case MSND_MIXER_VOLUME:		/* master volume */
		writew(wLeft, dev->SMA + SMA_wCurrMastVolLeft);
		writew(wRight, dev->SMA + SMA_wCurrMastVolRight);
		/* fall through */

	case MSND_MIXER_AUX:			/* aux pot control */
		/* scaled by master volume */
		/* fall through */

		/* digital controls */
	case MSND_MIXER_SYNTH:			/* synth vol (dsp mix) */
	case MSND_MIXER_PCM:			/* pcm vol (dsp mix) */
	case MSND_MIXER_IMIX:			/* input monitor (dsp mix) */
		/* scaled by master volume */
		updatemaster = 1;
		break;

	default:
		return -EINVAL;
	}

	if (updatemaster) {
		/* update master volume scaled controls */
		update_volm(MSND_MIXER_PCM, wCurrPlayVol);
		update_volm(MSND_MIXER_IMIX, wCurrInVol);
		if (dev->type == msndPinnacle)
			update_volm(MSND_MIXER_SYNTH, wCurrMHdrVol);
		update_potm(MSND_MIXER_AUX, bAuxPotPos, HDEXAR_AUX_SET_POTS);
	}

	return 0;
}