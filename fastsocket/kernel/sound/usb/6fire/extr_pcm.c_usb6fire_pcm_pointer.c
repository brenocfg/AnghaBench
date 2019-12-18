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
struct snd_pcm_substream {int dummy; } ;
struct pcm_substream {int /*<<< orphan*/  lock; int /*<<< orphan*/  dma_off; } ;
struct pcm_runtime {scalar_t__ panic; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STATE_XRUN ; 
 struct pcm_runtime* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pcm_substream* usb6fire_pcm_get_substream (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t usb6fire_pcm_pointer(
		struct snd_pcm_substream *alsa_sub)
{
	struct pcm_substream *sub = usb6fire_pcm_get_substream(alsa_sub);
	struct pcm_runtime *rt = snd_pcm_substream_chip(alsa_sub);
	unsigned long flags;
	snd_pcm_uframes_t ret;

	if (rt->panic || !sub)
		return SNDRV_PCM_STATE_XRUN;

	spin_lock_irqsave(&sub->lock, flags);
	ret = sub->dma_off;
	spin_unlock_irqrestore(&sub->lock, flags);
	return ret;
}