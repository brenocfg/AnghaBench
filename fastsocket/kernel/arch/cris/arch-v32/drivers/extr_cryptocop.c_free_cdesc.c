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
struct cryptocop_dma_desc {struct cryptocop_dma_desc* next; scalar_t__ from_pool; struct cryptocop_dma_desc* free_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ) ; 
 struct cryptocop_dma_desc* descr_pool_free_list ; 
 int /*<<< orphan*/  descr_pool_lock ; 
 int /*<<< orphan*/  descr_pool_no_free ; 
 int /*<<< orphan*/  kfree (struct cryptocop_dma_desc*) ; 
 int /*<<< orphan*/  printk (char*,struct cryptocop_dma_desc*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_cdesc(struct cryptocop_dma_desc *cdesc)
{
	DEBUG(printk("free_cdesc: cdesc 0x%p, from_pool=%d\n", cdesc, cdesc->from_pool));
	kfree(cdesc->free_buf);

	if (cdesc->from_pool) {
		unsigned long int flags;
		spin_lock_irqsave(&descr_pool_lock, flags);
		cdesc->next = descr_pool_free_list;
		descr_pool_free_list = cdesc;
		++descr_pool_no_free;
		spin_unlock_irqrestore(&descr_pool_lock, flags);
	} else {
		kfree(cdesc);
	}
}