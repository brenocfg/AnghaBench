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
struct sport_device {int /*<<< orphan*/  rx_dma_buf; int /*<<< orphan*/  tx_dma_buf; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int period_size; int /*<<< orphan*/  periods; int /*<<< orphan*/  dma_area; struct sport_device* private_data; } ;
struct ac97_frame {int dummy; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  bf5xx_dma_irq ; 
 int /*<<< orphan*/  sport_config_rx_dma (struct sport_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sport_config_tx_dma (struct sport_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sport_set_rx_callback (struct sport_device*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  sport_set_tx_callback (struct sport_device*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 

__attribute__((used)) static int bf5xx_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct sport_device *sport = runtime->private_data;

	/* An intermediate buffer is introduced for implementing mmap for
	 * SPORT working in TMD mode(include AC97).
	 */
#if defined(CONFIG_SND_BF5XX_MMAP_SUPPORT)
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		sport_set_tx_callback(sport, bf5xx_dma_irq, substream);
		sport_config_tx_dma(sport, sport->tx_dma_buf, runtime->periods,
			runtime->period_size * sizeof(struct ac97_frame));
	} else {
		sport_set_rx_callback(sport, bf5xx_dma_irq, substream);
		sport_config_rx_dma(sport, sport->rx_dma_buf, runtime->periods,
			runtime->period_size * sizeof(struct ac97_frame));
	}
#else
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		sport_set_tx_callback(sport, bf5xx_dma_irq, substream);
		sport_config_tx_dma(sport, runtime->dma_area, runtime->periods,
			runtime->period_size * sizeof(struct ac97_frame));
	} else {
		sport_set_rx_callback(sport, bf5xx_dma_irq, substream);
		sport_config_rx_dma(sport, runtime->dma_area, runtime->periods,
			runtime->period_size * sizeof(struct ac97_frame));
	}
#endif
	return 0;
}