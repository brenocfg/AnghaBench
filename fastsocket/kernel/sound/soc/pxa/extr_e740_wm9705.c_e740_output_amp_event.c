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
struct snd_soc_dapm_widget {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E740_AUDIO_OUT ; 
 int SND_SOC_DAPM_POST_PMD ; 
 int SND_SOC_DAPM_PRE_PMU ; 
 int /*<<< orphan*/  e740_audio_power ; 
 int /*<<< orphan*/  e740_sync_audio_power (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int e740_output_amp_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	if (event & SND_SOC_DAPM_PRE_PMU)
		e740_audio_power |= E740_AUDIO_OUT;
	else if (event & SND_SOC_DAPM_POST_PMD)
		e740_audio_power &= ~E740_AUDIO_OUT;

	e740_sync_audio_power(e740_audio_power);

	return 0;
}