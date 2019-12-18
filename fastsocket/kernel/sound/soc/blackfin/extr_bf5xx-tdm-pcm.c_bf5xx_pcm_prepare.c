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
struct sport_device {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  periods; int /*<<< orphan*/  dma_area; int /*<<< orphan*/  period_size; struct sport_device* private_data; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  bf5xx_dma_irq ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sport_config_rx_dma (struct sport_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sport_config_tx_dma (struct sport_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sport_set_rx_callback (struct sport_device*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  sport_set_tx_callback (struct sport_device*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 

__attribute__((used)) static int bf5xx_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct sport_device *sport = runtime->private_data;
	int fragsize_bytes = frames_to_bytes(runtime, runtime->period_size);

	fragsize_bytes /= runtime->channels;
	/* inflate the fragsize to match the dma width of SPORT */
	fragsize_bytes *= 8;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		sport_set_tx_callback(sport, bf5xx_dma_irq, substream);
		sport_config_tx_dma(sport, runtime->dma_area,
			runtime->periods, fragsize_bytes);
	} else {
		sport_set_rx_callback(sport, bf5xx_dma_irq, substream);
		sport_config_rx_dma(sport, runtime->dma_area,
			runtime->periods, fragsize_bytes);
	}

	return 0;
}