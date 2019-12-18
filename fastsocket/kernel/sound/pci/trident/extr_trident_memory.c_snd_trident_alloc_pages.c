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
struct snd_util_memblk {int dummy; } ;
struct snd_trident {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct snd_pcm_substream {TYPE_2__ dma_buffer; } ;

/* Variables and functions */
 scalar_t__ SNDRV_DMA_TYPE_DEV_SG ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct snd_util_memblk* snd_trident_alloc_cont_pages (struct snd_trident*,struct snd_pcm_substream*) ; 
 struct snd_util_memblk* snd_trident_alloc_sg_pages (struct snd_trident*,struct snd_pcm_substream*) ; 

struct snd_util_memblk *
snd_trident_alloc_pages(struct snd_trident *trident,
			struct snd_pcm_substream *substream)
{
	if (snd_BUG_ON(!trident || !substream))
		return NULL;
	if (substream->dma_buffer.dev.type == SNDRV_DMA_TYPE_DEV_SG)
		return snd_trident_alloc_sg_pages(trident, substream);
	else
		return snd_trident_alloc_cont_pages(trident, substream);
}