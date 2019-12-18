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
struct sport_device {unsigned int tx_delay_pos; unsigned int rx_pos; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct sport_device* private_data; } ;
struct ac97_frame {int dummy; } ;
typedef  unsigned int snd_pcm_uframes_t ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int sport_curr_offset_rx (struct sport_device*) ; 
 int sport_curr_offset_tx (struct sport_device*) ; 

__attribute__((used)) static snd_pcm_uframes_t bf5xx_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct sport_device *sport = runtime->private_data;
	unsigned int curr;

#if defined(CONFIG_SND_BF5XX_MMAP_SUPPORT)
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		curr = sport->tx_delay_pos;
	else
		curr = sport->rx_pos;
#else

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		curr = sport_curr_offset_tx(sport) / sizeof(struct ac97_frame);
	else
		curr = sport_curr_offset_rx(sport) / sizeof(struct ac97_frame);

#endif
	return curr;
}