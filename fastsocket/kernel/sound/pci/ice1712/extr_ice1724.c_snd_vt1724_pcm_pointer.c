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
struct vt1724_pcm_reg {size_t start; scalar_t__ size; scalar_t__ addr; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_ice1712 {scalar_t__ profi_port; } ;
typedef  size_t snd_pcm_uframes_t ;
struct TYPE_2__ {size_t buffer_size; scalar_t__ dma_addr; struct vt1724_pcm_reg* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CONTROL ; 
 scalar_t__ ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 size_t bytes_to_frames (TYPE_1__*,size_t) ; 
 size_t inl (scalar_t__) ; 
 size_t inw (scalar_t__) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_printd (char*,int,int) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_vt1724_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	const struct vt1724_pcm_reg *reg = substream->runtime->private_data;
	size_t ptr;

	if (!(inl(ICEMT1724(ice, DMA_CONTROL)) & reg->start))
		return 0;
#if 0 /* use ADDR register */
	ptr = inl(ice->profi_port + reg->addr);
	ptr -= substream->runtime->dma_addr;
	return bytes_to_frames(substream->runtime, ptr);
#else /* use SIZE register */
	ptr = inw(ice->profi_port + reg->size);
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
	return ptr;
#endif
}