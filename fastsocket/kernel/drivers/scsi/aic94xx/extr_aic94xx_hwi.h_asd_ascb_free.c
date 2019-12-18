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
struct TYPE_4__ {int /*<<< orphan*/  tc_index_lock; } ;
struct asd_ha_struct {int /*<<< orphan*/  scb_pool; TYPE_2__ seq; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  vaddr; } ;
struct asd_ascb {TYPE_1__ dma_scb; struct asd_ha_struct* ha; int /*<<< orphan*/  tc_index; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  asd_ascb_cache ; 
 int /*<<< orphan*/  asd_tc_index_release (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct asd_ascb*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void asd_ascb_free(struct asd_ascb *ascb)
{
	if (ascb) {
		struct asd_ha_struct *asd_ha = ascb->ha;
		unsigned long flags;

		BUG_ON(!list_empty(&ascb->list));
		spin_lock_irqsave(&ascb->ha->seq.tc_index_lock, flags);
		asd_tc_index_release(&ascb->ha->seq, ascb->tc_index);
		spin_unlock_irqrestore(&ascb->ha->seq.tc_index_lock, flags);
		dma_pool_free(asd_ha->scb_pool, ascb->dma_scb.vaddr,
			      ascb->dma_scb.dma_handle);
		kmem_cache_free(asd_ascb_cache, ascb);
	}
}