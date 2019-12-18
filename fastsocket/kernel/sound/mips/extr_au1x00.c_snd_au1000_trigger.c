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
struct snd_pcm_substream {struct audio_stream* private_data; } ;
struct audio_stream {int /*<<< orphan*/  dma_lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  au1000_dma_start (struct audio_stream*) ; 
 int /*<<< orphan*/  au1000_dma_stop (struct audio_stream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_au1000_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct audio_stream *stream = substream->private_data;
	int err = 0;

	spin_lock(&stream->dma_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		au1000_dma_start(stream);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		au1000_dma_stop(stream);
		break;
	default:
		err = -EINVAL;
		break;
	}
	spin_unlock(&stream->dma_lock);
	return err;
}