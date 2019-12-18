#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int spdif_sr; } ;
typedef  TYPE_1__ vortex_t ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; int /*<<< orphan*/  pcm; } ;
struct TYPE_8__ {int /*<<< orphan*/  rates; } ;
struct snd_pcm_runtime {int /*<<< orphan*/ * private_data; TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_32000 ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_44100 ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_48000 ; 
 scalar_t__ VORTEX_PCM_A3D ; 
 scalar_t__ VORTEX_PCM_ADB ; 
 scalar_t__ VORTEX_PCM_I2S ; 
 scalar_t__ VORTEX_PCM_SPDIF ; 
 scalar_t__ VORTEX_PCM_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VORTEX_PCM_WT ; 
 int snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_pow2 (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 TYPE_2__ snd_vortex_playback_hw_a3d ; 
 TYPE_2__ snd_vortex_playback_hw_adb ; 
 TYPE_2__ snd_vortex_playback_hw_spdif ; 
 TYPE_2__ snd_vortex_playback_hw_wt ; 

__attribute__((used)) static int snd_vortex_pcm_open(struct snd_pcm_substream *substream)
{
	vortex_t *vortex = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;
	
	/* Force equal size periods */
	if ((err =
	     snd_pcm_hw_constraint_integer(runtime,
					   SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		return err;
	/* Avoid PAGE_SIZE boundary to fall inside of a period. */
	if ((err =
	     snd_pcm_hw_constraint_pow2(runtime, 0,
					SNDRV_PCM_HW_PARAM_PERIOD_BYTES)) < 0)
		return err;

	if (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT) {
#ifndef CHIP_AU8820
		if (VORTEX_PCM_TYPE(substream->pcm) == VORTEX_PCM_A3D) {
			runtime->hw = snd_vortex_playback_hw_a3d;
		}
#endif
		if (VORTEX_PCM_TYPE(substream->pcm) == VORTEX_PCM_SPDIF) {
			runtime->hw = snd_vortex_playback_hw_spdif;
			switch (vortex->spdif_sr) {
			case 32000:
				runtime->hw.rates = SNDRV_PCM_RATE_32000;
				break;
			case 44100:
				runtime->hw.rates = SNDRV_PCM_RATE_44100;
				break;
			case 48000:
				runtime->hw.rates = SNDRV_PCM_RATE_48000;
				break;
			}
		}
		if (VORTEX_PCM_TYPE(substream->pcm) == VORTEX_PCM_ADB
		    || VORTEX_PCM_TYPE(substream->pcm) == VORTEX_PCM_I2S)
			runtime->hw = snd_vortex_playback_hw_adb;
		substream->runtime->private_data = NULL;
	}
#ifndef CHIP_AU8810
	else {
		runtime->hw = snd_vortex_playback_hw_wt;
		substream->runtime->private_data = NULL;
	}
#endif
	return 0;
}