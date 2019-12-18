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
struct snd_pcm_substream {int dummy; } ;
struct snd_emu10k1_pcm_mixer {int /*<<< orphan*/ * epcm; } ;
struct snd_emu10k1 {struct snd_emu10k1_pcm_mixer* efx_pcm_mixer; } ;

/* Variables and functions */
 int NUM_EFX_PLAYBACK ; 
 int /*<<< orphan*/  snd_emu10k1_pcm_efx_mixer_notify (struct snd_emu10k1*,int,int /*<<< orphan*/ ) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_emu10k1_efx_playback_close(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_emu10k1_pcm_mixer *mix;
	int i;

	for (i = 0; i < NUM_EFX_PLAYBACK; i++) {
		mix = &emu->efx_pcm_mixer[i];
		mix->epcm = NULL;
		snd_emu10k1_pcm_efx_mixer_notify(emu, i, 0);
	}
	return 0;
}