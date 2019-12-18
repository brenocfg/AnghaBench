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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __snd_util_mem_free (struct snd_util_memhdr*,struct snd_util_memblk*) ; 
 int firstpg (struct snd_util_memblk*) ; 
 int lastpg (struct snd_util_memblk*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_silent_tlb (struct snd_trident*,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 

int snd_trident_free_pages(struct snd_trident *trident,
			   struct snd_util_memblk *blk)
{
	struct snd_util_memhdr *hdr;
	int page;

	if (snd_BUG_ON(!trident || !blk))
		return -EINVAL;

	hdr = trident->tlb.memhdr;
	mutex_lock(&hdr->block_mutex);
	/* reset TLB entries */
	for (page = firstpg(blk); page <= lastpg(blk); page++)
		set_silent_tlb(trident, page);
	/* free memory block */
	__snd_util_mem_free(hdr, blk);
	mutex_unlock(&hdr->block_mutex);
	return 0;
}