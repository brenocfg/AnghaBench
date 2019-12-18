#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct TYPE_3__ {int /*<<< orphan*/  users; } ;
struct em28xx {int mute; int /*<<< orphan*/  lock; int /*<<< orphan*/  wq_trigger; int /*<<< orphan*/  stream_started; TYPE_1__ adev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dma_area; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  em28xx_audio_analog_set (struct em28xx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct em28xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_em28xx_pcm_close(struct snd_pcm_substream *substream)
{
	struct em28xx *dev = snd_pcm_substream_chip(substream);

	dprintk("closing device\n");

	dev->mute = 1;
	mutex_lock(&dev->lock);
	dev->adev.users--;
	if (atomic_read(&dev->stream_started) > 0) {
		atomic_set(&dev->stream_started, 0);
		schedule_work(&dev->wq_trigger);
	}

	em28xx_audio_analog_set(dev);
	if (substream->runtime->dma_area) {
		dprintk("freeing\n");
		vfree(substream->runtime->dma_area);
		substream->runtime->dma_area = NULL;
	}
	mutex_unlock(&dev->lock);

	return 0;
}