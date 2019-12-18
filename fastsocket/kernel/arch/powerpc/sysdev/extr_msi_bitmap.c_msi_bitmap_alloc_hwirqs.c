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
struct msi_bitmap {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_count; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int bitmap_find_free_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int get_count_order (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int msi_bitmap_alloc_hwirqs(struct msi_bitmap *bmp, int num)
{
	unsigned long flags;
	int offset, order = get_count_order(num);

	spin_lock_irqsave(&bmp->lock, flags);
	/*
	 * This is fast, but stricter than we need. We might want to add
	 * a fallback routine which does a linear search with no alignment.
	 */
	offset = bitmap_find_free_region(bmp->bitmap, bmp->irq_count, order);
	spin_unlock_irqrestore(&bmp->lock, flags);

	pr_debug("msi_bitmap: allocated 0x%x (2^%d) at offset 0x%x\n",
		 num, order, offset);

	return offset;
}