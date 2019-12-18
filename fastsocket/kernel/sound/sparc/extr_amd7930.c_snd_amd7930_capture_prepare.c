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
typedef  int /*<<< orphan*/  u8 ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ format; int /*<<< orphan*/  dma_area; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmr1; } ;
struct snd_amd7930 {unsigned int c_left; int /*<<< orphan*/  lock; TYPE_1__ map; int /*<<< orphan*/  c_cur; int /*<<< orphan*/  c_orig; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD7930_FLAG_CAPTURE ; 
 int /*<<< orphan*/  AM_MAP_MMR1_ALAW ; 
 scalar_t__ SNDRV_PCM_FORMAT_A_LAW ; 
 int /*<<< orphan*/  __amd7930_update_map (struct snd_amd7930*) ; 
 unsigned int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 struct snd_amd7930* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_amd7930_capture_prepare(struct snd_pcm_substream *substream)
{
	struct snd_amd7930 *amd = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned int size = snd_pcm_lib_buffer_bytes(substream);
	unsigned long flags;
	u8 new_mmr1;

	spin_lock_irqsave(&amd->lock, flags);

	amd->flags |= AMD7930_FLAG_CAPTURE;

	/* Setup the pseudo-dma transfer pointers.  */
	amd->c_orig = amd->c_cur = runtime->dma_area;
	amd->c_left = size;

	/* Put the chip into the correct encoding format.  */
	new_mmr1 = amd->map.mmr1;
	if (runtime->format == SNDRV_PCM_FORMAT_A_LAW)
		new_mmr1 |= AM_MAP_MMR1_ALAW;
	else
		new_mmr1 &= ~AM_MAP_MMR1_ALAW;
	if (new_mmr1 != amd->map.mmr1) {
		amd->map.mmr1 = new_mmr1;
		__amd7930_update_map(amd);
	}

	spin_unlock_irqrestore(&amd->lock, flags);

	return 0;
}