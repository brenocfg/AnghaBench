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
struct msi_bitmap {unsigned int irq_count; int /*<<< orphan*/  of_node; int /*<<< orphan*/  lock; int /*<<< orphan*/  bitmap; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int BITS_TO_LONGS (unsigned int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zalloc_maybe_bootmem (int,int /*<<< orphan*/ ) ; 

int msi_bitmap_alloc(struct msi_bitmap *bmp, unsigned int irq_count,
		     struct device_node *of_node)
{
	int size;

	if (!irq_count)
		return -EINVAL;

	size = BITS_TO_LONGS(irq_count) * sizeof(long);
	pr_debug("msi_bitmap: allocator bitmap size is 0x%x bytes\n", size);

	bmp->bitmap = zalloc_maybe_bootmem(size, GFP_KERNEL);
	if (!bmp->bitmap) {
		pr_debug("msi_bitmap: ENOMEM allocating allocator bitmap!\n");
		return -ENOMEM;
	}

	/* We zalloc'ed the bitmap, so all irqs are free by default */
	spin_lock_init(&bmp->lock);
	bmp->of_node = of_node_get(of_node);
	bmp->irq_count = irq_count;

	return 0;
}