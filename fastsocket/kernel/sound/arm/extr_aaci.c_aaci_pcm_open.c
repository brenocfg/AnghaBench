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
struct snd_pcm_substream {scalar_t__ stream; int /*<<< orphan*/  runtime; struct aaci* private_data; } ;
struct aaci {int /*<<< orphan*/  capture; int /*<<< orphan*/  playback; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int __aaci_pcm_open (struct aaci*,struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aaci_rule_channels ; 
 int snd_pcm_hw_rule_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aaci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aaci_pcm_open(struct snd_pcm_substream *substream)
{
	struct aaci *aaci = substream->private_data;
	int ret;

	/*
	 * Add rule describing channel dependency.
	 */
	ret = snd_pcm_hw_rule_add(substream->runtime, 0,
				  SNDRV_PCM_HW_PARAM_CHANNELS,
				  aaci_rule_channels, aaci,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	if (ret)
		return ret;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		ret = __aaci_pcm_open(aaci, substream, &aaci->playback);
	} else {
		ret = __aaci_pcm_open(aaci, substream, &aaci->capture);
	}
	return ret;
}