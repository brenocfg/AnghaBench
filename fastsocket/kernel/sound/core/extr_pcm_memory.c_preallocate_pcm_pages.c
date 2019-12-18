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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  type; } ;
struct snd_dma_buffer {size_t bytes; TYPE_1__ dev; } ;
struct snd_pcm_substream {int /*<<< orphan*/  dma_buf_id; struct snd_dma_buffer dma_buffer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int snd_dma_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,struct snd_dma_buffer*) ; 
 int /*<<< orphan*/  snd_dma_free_pages (struct snd_dma_buffer*) ; 
 scalar_t__ snd_dma_get_reserved_buf (struct snd_dma_buffer*,int /*<<< orphan*/ ) ; 
 size_t snd_minimum_buffer ; 

__attribute__((used)) static int preallocate_pcm_pages(struct snd_pcm_substream *substream, size_t size)
{
	struct snd_dma_buffer *dmab = &substream->dma_buffer;
	int err;

	/* already reserved? */
	if (snd_dma_get_reserved_buf(dmab, substream->dma_buf_id) > 0) {
		if (dmab->bytes >= size)
			return 0; /* yes */
		/* no, free the reserved block */
		snd_dma_free_pages(dmab);
		dmab->bytes = 0;
	}

	do {
		if ((err = snd_dma_alloc_pages(dmab->dev.type, dmab->dev.dev,
					       size, dmab)) < 0) {
			if (err != -ENOMEM)
				return err; /* fatal error */
		} else
			return 0;
		size >>= 1;
	} while (size >= snd_minimum_buffer);
	dmab->bytes = 0; /* tell error */
	return 0;
}