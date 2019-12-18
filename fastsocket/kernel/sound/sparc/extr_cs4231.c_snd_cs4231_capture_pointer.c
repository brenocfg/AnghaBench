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
struct cs4231_dma_control {size_t (* address ) (struct cs4231_dma_control*) ;} ;
struct snd_cs4231 {int* image; struct cs4231_dma_control c_dma; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_2__ {scalar_t__ dma_addr; } ;

/* Variables and functions */
 size_t CS4231_IFACE_CTRL ; 
 int CS4231_RECORD_ENABLE ; 
 int /*<<< orphan*/  bytes_to_frames (TYPE_1__*,size_t) ; 
 struct snd_cs4231* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 size_t stub1 (struct cs4231_dma_control*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_cs4231_capture_pointer(
					struct snd_pcm_substream *substream)
{
	struct snd_cs4231 *chip = snd_pcm_substream_chip(substream);
	struct cs4231_dma_control *dma_cont = &chip->c_dma;
	size_t ptr;

	if (!(chip->image[CS4231_IFACE_CTRL] & CS4231_RECORD_ENABLE))
		return 0;
	ptr = dma_cont->address(dma_cont);
	if (ptr != 0)
		ptr -= substream->runtime->dma_addr;

	return bytes_to_frames(substream->runtime, ptr);
}