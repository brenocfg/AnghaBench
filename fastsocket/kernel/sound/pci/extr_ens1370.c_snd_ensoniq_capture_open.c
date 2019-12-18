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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;
struct ensoniq {struct snd_pcm_substream* capture_substream; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES_MODE_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  snd_ensoniq_capture ; 
 int /*<<< orphan*/  snd_es1370_hw_constraints_clock ; 
 int /*<<< orphan*/  snd_es1371_hw_constraints_adc_clock ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_ratnums (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 struct ensoniq* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_ensoniq_capture_open(struct snd_pcm_substream *substream)
{
	struct ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	ensoniq->mode |= ES_MODE_CAPTURE;
	ensoniq->capture_substream = substream;
	runtime->hw = snd_ensoniq_capture;
	snd_pcm_set_sync(substream);
#ifdef CHIP1370
	snd_pcm_hw_constraint_ratnums(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &snd_es1370_hw_constraints_clock);
#else
	snd_pcm_hw_constraint_ratnums(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &snd_es1371_hw_constraints_adc_clock);
#endif
	return 0;
}