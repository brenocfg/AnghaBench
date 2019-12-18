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
struct vmap_block {scalar_t__ dirty; int free; int /*<<< orphan*/  lock; int /*<<< orphan*/  dirty_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ VMAP_BBMAP_BITS ; 
 int VMAP_BLOCK_SIZE ; 
 unsigned long VMAP_MAX_ALLOC ; 
 unsigned long addr_to_vb_idx (unsigned long) ; 
 int bitmap_allocate_region (int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  flush_cache_vunmap (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  free_vmap_block (struct vmap_block*) ; 
 unsigned int get_order (unsigned long) ; 
 struct vmap_block* radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmap_block_tree ; 
 int /*<<< orphan*/  vunmap_page_range (unsigned long,unsigned long) ; 

__attribute__((used)) static void vb_free(const void *addr, unsigned long size)
{
	unsigned long offset;
	unsigned long vb_idx;
	unsigned int order;
	struct vmap_block *vb;

	BUG_ON(size & ~PAGE_MASK);
	BUG_ON(size > PAGE_SIZE*VMAP_MAX_ALLOC);

	flush_cache_vunmap((unsigned long)addr, (unsigned long)addr + size);

	order = get_order(size);

	offset = (unsigned long)addr & (VMAP_BLOCK_SIZE - 1);

	vb_idx = addr_to_vb_idx((unsigned long)addr);
	rcu_read_lock();
	vb = radix_tree_lookup(&vmap_block_tree, vb_idx);
	rcu_read_unlock();
	BUG_ON(!vb);

	vunmap_page_range((unsigned long)addr, (unsigned long)addr + size);

	spin_lock(&vb->lock);
	BUG_ON(bitmap_allocate_region(vb->dirty_map, offset >> PAGE_SHIFT, order));

	vb->dirty += 1UL << order;
	if (vb->dirty == VMAP_BBMAP_BITS) {
		BUG_ON(vb->free);
		spin_unlock(&vb->lock);
		free_vmap_block(vb);
	} else
		spin_unlock(&vb->lock);
}