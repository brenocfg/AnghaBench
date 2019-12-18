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
struct snd_sgio2audio_chan {int idx; } ;
struct snd_sgio2audio {TYPE_1__* channel; int /*<<< orphan*/  ad1843; } ;
struct snd_pcm_substream {int stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  channels; int /*<<< orphan*/  rate; struct snd_sgio2audio_chan* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct snd_pcm_substream* substream; scalar_t__ size; scalar_t__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_FORMAT_S16_LE ; 
#define  SNDRV_PCM_STREAM_CAPTURE 129 
#define  SNDRV_PCM_STREAM_PLAYBACK 128 
 int /*<<< orphan*/  ad1843_setup_adc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad1843_setup_dac (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_sgio2audio* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_sgio2audio_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_sgio2audio *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_sgio2audio_chan *chan = substream->runtime->private_data;
	int ch = chan->idx;
	unsigned long flags;

	spin_lock_irqsave(&chip->channel[ch].lock, flags);

	/* Setup the pseudo-dma transfer pointers.  */
	chip->channel[ch].pos = 0;
	chip->channel[ch].size = 0;
	chip->channel[ch].substream = substream;

	/* set AD1843 format */
	/* hardware format is always S16_LE */
	switch (substream->stream) {
	case SNDRV_PCM_STREAM_PLAYBACK:
		ad1843_setup_dac(&chip->ad1843,
				 ch - 1,
				 runtime->rate,
				 SNDRV_PCM_FORMAT_S16_LE,
				 runtime->channels);
		break;
	case SNDRV_PCM_STREAM_CAPTURE:
		ad1843_setup_adc(&chip->ad1843,
				 runtime->rate,
				 SNDRV_PCM_FORMAT_S16_LE,
				 runtime->channels);
		break;
	}
	spin_unlock_irqrestore(&chip->channel[ch].lock, flags);
	return 0;
}