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
struct snd_util_memhdr {int /*<<< orphan*/  block_mutex; } ;
struct snd_util_memblk {int dummy; } ;
struct snd_emu10k1_memblk {scalar_t__ mapped_page; } ;
struct snd_emu10k1 {int /*<<< orphan*/  memblk_lock; struct snd_util_memhdr* memhdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __snd_util_mem_free (struct snd_util_memhdr*,struct snd_util_memblk*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synth_free_pages (struct snd_emu10k1*,struct snd_emu10k1_memblk*) ; 
 int /*<<< orphan*/  unmap_memblk (struct snd_emu10k1*,struct snd_emu10k1_memblk*) ; 

int
snd_emu10k1_synth_free(struct snd_emu10k1 *emu, struct snd_util_memblk *memblk)
{
	struct snd_util_memhdr *hdr = emu->memhdr; 
	struct snd_emu10k1_memblk *blk = (struct snd_emu10k1_memblk *)memblk;
	unsigned long flags;

	mutex_lock(&hdr->block_mutex);
	spin_lock_irqsave(&emu->memblk_lock, flags);
	if (blk->mapped_page >= 0)
		unmap_memblk(emu, blk);
	spin_unlock_irqrestore(&emu->memblk_lock, flags);
	synth_free_pages(emu, blk);
	 __snd_util_mem_free(hdr, memblk);
	mutex_unlock(&hdr->block_mutex);
	return 0;
}