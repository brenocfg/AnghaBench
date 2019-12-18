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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;
struct hdspm {scalar_t__ is_aes32; int /*<<< orphan*/  lock; struct snd_pcm_substream* playback_substream; int /*<<< orphan*/  playback_pid; int /*<<< orphan*/ * capture_substream; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  hdspm_hw_constraints_aes32_sample_rates ; 
 int /*<<< orphan*/  hdspm_stop_audio (struct hdspm*) ; 
 int /*<<< orphan*/  hw_constraints_period_sizes ; 
 int /*<<< orphan*/  snd_hdspm_hw_rule_channels ; 
 int /*<<< orphan*/  snd_hdspm_hw_rule_channels_rate ; 
 int /*<<< orphan*/  snd_hdspm_hw_rule_rate_channels ; 
 int /*<<< orphan*/  snd_hdspm_playback_subinfo ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_msbits (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hdspm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 struct hdspm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hdspm_playback_open(struct snd_pcm_substream *substream)
{
	struct hdspm *hdspm = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	spin_lock_irq(&hdspm->lock);

	snd_pcm_set_sync(substream);

	runtime->hw = snd_hdspm_playback_subinfo;

	if (hdspm->capture_substream == NULL)
		hdspm_stop_audio(hdspm);

	hdspm->playback_pid = current->pid;
	hdspm->playback_substream = substream;

	spin_unlock_irq(&hdspm->lock);

	snd_pcm_hw_constraint_msbits(runtime, 0, 32, 24);

	snd_pcm_hw_constraint_list(runtime, 0,
				   SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
				   &hw_constraints_period_sizes);

	if (hdspm->is_aes32) {
		snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				&hdspm_hw_constraints_aes32_sample_rates);
	} else {
		snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				     snd_hdspm_hw_rule_channels, hdspm,
				     SNDRV_PCM_HW_PARAM_CHANNELS, -1);
		snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				    snd_hdspm_hw_rule_channels_rate, hdspm,
				    SNDRV_PCM_HW_PARAM_RATE, -1);

		snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				    snd_hdspm_hw_rule_rate_channels, hdspm,
				    SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	}
	return 0;
}