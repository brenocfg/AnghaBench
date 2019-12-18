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
struct pnx4008_dma_ll {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int count; int dma_addr; void* vaddr; scalar_t__ cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  ll_lock ; 
 TYPE_1__ ll_pool ; 
 int /*<<< orphan*/  memset (struct pnx4008_dma_ll*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct pnx4008_dma_ll *pnx4008_alloc_ll_entry(dma_addr_t * ll_dma)
{
	struct pnx4008_dma_ll *ll = NULL;
	unsigned long flags;

	spin_lock_irqsave(&ll_lock, flags);
	if (ll_pool.count > 4) { /* can give one more */
		ll = *(struct pnx4008_dma_ll **) ll_pool.cur;
		*ll_dma = ll_pool.dma_addr + ((void *)ll - ll_pool.vaddr);
		*(void **)ll_pool.cur = **(void ***)ll_pool.cur;
		memset(ll, 0, sizeof(*ll));
		ll_pool.count--;
	}
	spin_unlock_irqrestore(&ll_lock, flags);

	return ll;
}