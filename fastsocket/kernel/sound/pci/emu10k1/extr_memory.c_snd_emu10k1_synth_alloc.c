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
struct snd_emu10k1_memblk {int dummy; } ;
struct snd_emu10k1 {struct snd_util_memhdr* memhdr; } ;

/* Variables and functions */
 scalar_t__ __snd_util_mem_alloc (struct snd_util_memhdr*,unsigned int) ; 
 int /*<<< orphan*/  __snd_util_mem_free (struct snd_util_memhdr*,struct snd_util_memblk*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_emu10k1_memblk_map (struct snd_emu10k1*,struct snd_emu10k1_memblk*) ; 
 scalar_t__ synth_alloc_pages (struct snd_emu10k1*,struct snd_emu10k1_memblk*) ; 

struct snd_util_memblk *
snd_emu10k1_synth_alloc(struct snd_emu10k1 *hw, unsigned int size)
{
	struct snd_emu10k1_memblk *blk;
	struct snd_util_memhdr *hdr = hw->memhdr; 

	mutex_lock(&hdr->block_mutex);
	blk = (struct snd_emu10k1_memblk *)__snd_util_mem_alloc(hdr, size);
	if (blk == NULL) {
		mutex_unlock(&hdr->block_mutex);
		return NULL;
	}
	if (synth_alloc_pages(hw, blk)) {
		__snd_util_mem_free(hdr, (struct snd_util_memblk *)blk);
		mutex_unlock(&hdr->block_mutex);
		return NULL;
	}
	snd_emu10k1_memblk_map(hw, blk);
	mutex_unlock(&hdr->block_mutex);
	return (struct snd_util_memblk *)blk;
}