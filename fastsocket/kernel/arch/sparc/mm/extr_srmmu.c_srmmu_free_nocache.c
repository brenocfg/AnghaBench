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

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int SRMMU_NOCACHE_BITMAP_SHIFT ; 
 unsigned long SRMMU_NOCACHE_VADDR ; 
 int /*<<< orphan*/  bit_map_clear (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  printk (char*,unsigned long,...) ; 
 unsigned long srmmu_nocache_end ; 
 int /*<<< orphan*/  srmmu_nocache_map ; 

__attribute__((used)) static void srmmu_free_nocache(unsigned long vaddr, int size)
{
	int offset;

	if (vaddr < SRMMU_NOCACHE_VADDR) {
		printk("Vaddr %lx is smaller than nocache base 0x%lx\n",
		    vaddr, (unsigned long)SRMMU_NOCACHE_VADDR);
		BUG();
	}
	if (vaddr+size > srmmu_nocache_end) {
		printk("Vaddr %lx is bigger than nocache end 0x%lx\n",
		    vaddr, srmmu_nocache_end);
		BUG();
	}
	if (!is_power_of_2(size)) {
		printk("Size 0x%x is not a power of 2\n", size);
		BUG();
	}
	if (size < SRMMU_NOCACHE_BITMAP_SHIFT) {
		printk("Size 0x%x is too small\n", size);
		BUG();
	}
	if (vaddr & (size-1)) {
		printk("Vaddr %lx is not aligned to size 0x%x\n", vaddr, size);
		BUG();
	}

	offset = (vaddr - SRMMU_NOCACHE_VADDR) >> SRMMU_NOCACHE_BITMAP_SHIFT;
	size = size >> SRMMU_NOCACHE_BITMAP_SHIFT;

	bit_map_clear(&srmmu_nocache_map, offset, size);
}