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
struct msi_bitmap {int /*<<< orphan*/  lock; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,unsigned int,int) ; 
 int get_count_order (unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void msi_bitmap_free_hwirqs(struct msi_bitmap *bmp, unsigned int offset,
			    unsigned int num)
{
	unsigned long flags;
	int order = get_count_order(num);

	pr_debug("msi_bitmap: freeing 0x%x (2^%d) at offset 0x%x\n",
		 num, order, offset);

	spin_lock_irqsave(&bmp->lock, flags);
	bitmap_release_region(bmp->bitmap, offset, order);
	spin_unlock_irqrestore(&bmp->lock, flags);
}