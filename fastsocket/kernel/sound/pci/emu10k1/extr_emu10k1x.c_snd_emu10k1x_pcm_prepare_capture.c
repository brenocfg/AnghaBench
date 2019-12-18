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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int dma_addr; int /*<<< orphan*/  buffer_size; } ;
struct emu10k1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPTURE_BUFFER_SIZE ; 
 int /*<<< orphan*/  CAPTURE_DMA_ADDR ; 
 int /*<<< orphan*/  CAPTURE_POINTER ; 
 int /*<<< orphan*/  CAPTURE_UNKNOWN ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1x_ptr_write (struct emu10k1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct emu10k1x* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_emu10k1x_pcm_prepare_capture(struct snd_pcm_substream *substream)
{
	struct emu10k1x *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	snd_emu10k1x_ptr_write(emu, CAPTURE_DMA_ADDR, 0, runtime->dma_addr);
	snd_emu10k1x_ptr_write(emu, CAPTURE_BUFFER_SIZE, 0, frames_to_bytes(runtime, runtime->buffer_size)<<16); // buffer size in bytes
	snd_emu10k1x_ptr_write(emu, CAPTURE_POINTER, 0, 0);
	snd_emu10k1x_ptr_write(emu, CAPTURE_UNKNOWN, 0, 0);

	return 0;
}