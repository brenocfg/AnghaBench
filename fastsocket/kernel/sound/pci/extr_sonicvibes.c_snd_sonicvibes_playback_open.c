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
struct sonicvibes {struct snd_pcm_substream* playback_substream; int /*<<< orphan*/  mode; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  SV_MODE_PLAY ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct sonicvibes* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_sonicvibes_hw_constraint_dac_rate ; 
 int /*<<< orphan*/  snd_sonicvibes_playback ; 

__attribute__((used)) static int snd_sonicvibes_playback_open(struct snd_pcm_substream *substream)
{
	struct sonicvibes *sonic = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	sonic->mode |= SV_MODE_PLAY;
	sonic->playback_substream = substream;
	runtime->hw = snd_sonicvibes_playback;
	snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE, snd_sonicvibes_hw_constraint_dac_rate, NULL, SNDRV_PCM_HW_PARAM_RATE, -1);
	return 0;
}