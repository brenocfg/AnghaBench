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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_ice1712 {int dummy; } ;
typedef  size_t snd_pcm_uframes_t ;
struct TYPE_2__ {size_t dma_addr; size_t buffer_size; scalar_t__ period_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CONTROL ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLAYBACK_ADDR ; 
 int /*<<< orphan*/  PLAYBACK_SIZE ; 
 int VT1724_PDMA0_START ; 
 size_t bytes_to_frames (TYPE_1__*,size_t) ; 
 int inl (int /*<<< orphan*/ ) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_printd (char*,...) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_vt1724_playback_pro_pointer(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	size_t ptr;

	if (!(inl(ICEMT1724(ice, DMA_CONTROL)) & VT1724_PDMA0_START))
		return 0;
#if 0 /* read PLAYBACK_ADDR */
	ptr = inl(ICEMT1724(ice, PLAYBACK_ADDR));
	if (ptr < substream->runtime->dma_addr) {
		snd_printd("ice1724: invalid negative ptr\n");
		return 0;
	}
	ptr -= substream->runtime->dma_addr;
	ptr = bytes_to_frames(substream->runtime, ptr);
	if (ptr >= substream->runtime->buffer_size) {
		snd_printd("ice1724: invalid ptr %d (size=%d)\n",
			   (int)ptr, (int)substream->runtime->period_size);
		return 0;
	}
#else /* read PLAYBACK_SIZE */
	ptr = inl(ICEMT1724(ice, PLAYBACK_SIZE)) & 0xffffff;
	ptr = (ptr + 1) << 2;
	ptr = bytes_to_frames(substream->runtime, ptr);
	if (!ptr)
		;
	else if (ptr <= substream->runtime->buffer_size)
		ptr = substream->runtime->buffer_size - ptr;
	else {
		snd_printd("ice1724: invalid ptr %d (size=%d)\n",
			   (int)ptr, (int)substream->runtime->buffer_size);
		ptr = 0;
	}
#endif
	return ptr;
}