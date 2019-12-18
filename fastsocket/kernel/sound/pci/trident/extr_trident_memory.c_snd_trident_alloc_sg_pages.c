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
struct snd_util_memhdr {int /*<<< orphan*/  block_mutex; } ;
struct snd_util_memblk {int dummy; } ;
struct TYPE_2__ {struct snd_util_memhdr* memhdr; } ;
struct snd_trident {TYPE_1__ tlb; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int dma_bytes; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int SNDRV_TRIDENT_MAX_PAGES ; 
 int SNDRV_TRIDENT_PAGE_SIZE ; 
 int /*<<< orphan*/  __snd_util_mem_free (struct snd_util_memhdr*,struct snd_util_memblk*) ; 
 int firstpg (struct snd_util_memblk*) ; 
 int /*<<< orphan*/  is_valid_page (int /*<<< orphan*/ ) ; 
 int lastpg (struct snd_util_memblk*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_util_memblk* search_empty (struct snd_util_memhdr*,int) ; 
 int /*<<< orphan*/  set_tlb_bus (struct snd_trident*,int,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_pcm_sgbuf_get_addr (struct snd_pcm_substream*,unsigned long) ; 
 scalar_t__ snd_pcm_sgbuf_get_ptr (struct snd_pcm_substream*,unsigned long) ; 

__attribute__((used)) static struct snd_util_memblk *
snd_trident_alloc_sg_pages(struct snd_trident *trident,
			   struct snd_pcm_substream *substream)
{
	struct snd_util_memhdr *hdr;
	struct snd_util_memblk *blk;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int idx, page;

	if (snd_BUG_ON(runtime->dma_bytes <= 0 ||
		       runtime->dma_bytes > SNDRV_TRIDENT_MAX_PAGES *
					SNDRV_TRIDENT_PAGE_SIZE))
		return NULL;
	hdr = trident->tlb.memhdr;
	if (snd_BUG_ON(!hdr))
		return NULL;

	

	mutex_lock(&hdr->block_mutex);
	blk = search_empty(hdr, runtime->dma_bytes);
	if (blk == NULL) {
		mutex_unlock(&hdr->block_mutex);
		return NULL;
	}
			   
	/* set TLB entries */
	idx = 0;
	for (page = firstpg(blk); page <= lastpg(blk); page++, idx++) {
		unsigned long ofs = idx << PAGE_SHIFT;
		dma_addr_t addr = snd_pcm_sgbuf_get_addr(substream, ofs);
		unsigned long ptr = (unsigned long)
			snd_pcm_sgbuf_get_ptr(substream, ofs);
		if (! is_valid_page(addr)) {
			__snd_util_mem_free(hdr, blk);
			mutex_unlock(&hdr->block_mutex);
			return NULL;
		}
		set_tlb_bus(trident, page, ptr, addr);
	}
	mutex_unlock(&hdr->block_mutex);
	return blk;
}