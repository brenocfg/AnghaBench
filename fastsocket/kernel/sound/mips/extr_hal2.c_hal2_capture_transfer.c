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
struct snd_pcm_indirect {int hw_data; scalar_t__ sw_data; } ;
struct TYPE_3__ {unsigned char* buffer; } ;
struct snd_hal2 {TYPE_1__ adc; } ;
struct TYPE_4__ {scalar_t__ dma_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_cache_sync (int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char*,size_t) ; 
 struct snd_hal2* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static void hal2_capture_transfer(struct snd_pcm_substream *substream,
				  struct snd_pcm_indirect *rec, size_t bytes)
{
	struct snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	unsigned char *buf = hal2->adc.buffer + rec->hw_data;

	dma_cache_sync(NULL, buf, bytes, DMA_FROM_DEVICE);
	memcpy(substream->runtime->dma_area + rec->sw_data, buf, bytes);
}