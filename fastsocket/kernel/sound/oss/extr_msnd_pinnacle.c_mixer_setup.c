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

/* Variables and functions */
 int /*<<< orphan*/  HDEXAR_AUX_SET_POTS ; 
 int /*<<< orphan*/  HDEXAR_IN_SET_POTS ; 
 int /*<<< orphan*/  HDEXAR_MIC_SET_POTS ; 
 int /*<<< orphan*/  SOUND_MIXER_IMIX ; 
 int /*<<< orphan*/  SOUND_MIXER_LINE ; 
 int /*<<< orphan*/  SOUND_MIXER_LINE1 ; 
 int /*<<< orphan*/  SOUND_MIXER_MIC ; 
 int /*<<< orphan*/  SOUND_MIXER_PCM ; 
 int /*<<< orphan*/  SOUND_MIXER_SYNTH ; 
 int /*<<< orphan*/  bAuxPotPos ; 
 int /*<<< orphan*/  bInPotPos ; 
 int /*<<< orphan*/  bMicPotPos ; 
 int /*<<< orphan*/  update_pot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_potm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_volm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wCurrInVol ; 
 int /*<<< orphan*/  wCurrMHdrVol ; 
 int /*<<< orphan*/  wCurrPlayVol ; 

__attribute__((used)) static void mixer_setup(void)
{
	update_pot(SOUND_MIXER_LINE, bInPotPos, HDEXAR_IN_SET_POTS);
	update_potm(SOUND_MIXER_LINE1, bAuxPotPos, HDEXAR_AUX_SET_POTS);
	update_volm(SOUND_MIXER_PCM, wCurrPlayVol);
	update_volm(SOUND_MIXER_IMIX, wCurrInVol);
#ifndef MSND_CLASSIC
	update_pot(SOUND_MIXER_MIC, bMicPotPos, HDEXAR_MIC_SET_POTS);
	update_volm(SOUND_MIXER_SYNTH, wCurrMHdrVol);
#endif
}