#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int rates; unsigned int rate_min; unsigned int rate_max; } ;
struct TYPE_4__ {unsigned int rates; unsigned int rate_min; unsigned int rate_max; } ;
struct snd_soc_dai {TYPE_2__ capture; TYPE_1__ playback; struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int /*<<< orphan*/  dev; struct cs4270_private* private_data; } ;
struct cs4270_private {unsigned int mclk; } ;
struct TYPE_6__ {unsigned int ratio; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NUM_MCLK_RATIOS ; 
 unsigned int SNDRV_PCM_RATE_KNOT ; 
 TYPE_3__* cs4270_mode_ratios ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int snd_pcm_rate_to_rate_bit (unsigned int) ; 

__attribute__((used)) static int cs4270_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				 int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct cs4270_private *cs4270 = codec->private_data;
	unsigned int rates = 0;
	unsigned int rate_min = -1;
	unsigned int rate_max = 0;
	unsigned int i;

	cs4270->mclk = freq;

	for (i = 0; i < NUM_MCLK_RATIOS; i++) {
		unsigned int rate = freq / cs4270_mode_ratios[i].ratio;
		rates |= snd_pcm_rate_to_rate_bit(rate);
		if (rate < rate_min)
			rate_min = rate;
		if (rate > rate_max)
			rate_max = rate;
	}
	/* FIXME: soc should support a rate list */
	rates &= ~SNDRV_PCM_RATE_KNOT;

	if (!rates) {
		dev_err(codec->dev, "could not find a valid sample rate\n");
		return -EINVAL;
	}

	codec_dai->playback.rates = rates;
	codec_dai->playback.rate_min = rate_min;
	codec_dai->playback.rate_max = rate_max;

	codec_dai->capture.rates = rates;
	codec_dai->capture.rate_min = rate_min;
	codec_dai->capture.rate_max = rate_max;

	return 0;
}