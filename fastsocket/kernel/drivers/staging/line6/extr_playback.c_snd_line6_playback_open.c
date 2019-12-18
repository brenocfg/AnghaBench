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
struct snd_line6_pcm {TYPE_1__* properties; } ;
struct TYPE_2__ {int /*<<< orphan*/  snd_line6_playback_hw; int /*<<< orphan*/  snd_line6_rates; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int snd_pcm_hw_constraint_ratdens (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_line6_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_line6_playback_open(struct snd_pcm_substream *substream)
{
	int err;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);

	err = snd_pcm_hw_constraint_ratdens(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
					    (&line6pcm->properties->snd_line6_rates));
	if (err < 0)
		return err;

	runtime->hw = line6pcm->properties->snd_line6_playback_hw;
	return 0;
}