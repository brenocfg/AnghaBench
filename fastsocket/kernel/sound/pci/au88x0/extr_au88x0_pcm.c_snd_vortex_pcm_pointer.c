#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vortex_t ;
struct snd_pcm_substream {TYPE_6__* runtime; int /*<<< orphan*/  pcm; } ;
struct TYPE_8__ {int dma; } ;
typedef  TYPE_2__ stream_t ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_9__ {scalar_t__ private_data; } ;

/* Variables and functions */
 scalar_t__ VORTEX_PCM_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VORTEX_PCM_WT ; 
 int /*<<< orphan*/  bytes_to_frames (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vortex_adbdma_getlinearpos (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vortex_wtdma_getlinearpos (TYPE_1__*,int) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_vortex_pcm_pointer(struct snd_pcm_substream *substream)
{
	vortex_t *chip = snd_pcm_substream_chip(substream);
	stream_t *stream = (stream_t *) substream->runtime->private_data;
	int dma = stream->dma;
	snd_pcm_uframes_t current_ptr = 0;

	spin_lock(&chip->lock);
	if (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT)
		current_ptr = vortex_adbdma_getlinearpos(chip, dma);
#ifndef CHIP_AU8810
	else
		current_ptr = vortex_wtdma_getlinearpos(chip, dma);
#endif
	//printk(KERN_INFO "vortex: pointer = 0x%x\n", current_ptr);
	spin_unlock(&chip->lock);
	return (bytes_to_frames(substream->runtime, current_ptr));
}