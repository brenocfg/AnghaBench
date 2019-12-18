#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int used; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SRMMU_NOCACHE_ALIGN_MAX ; 
 int SRMMU_NOCACHE_BITMAP_SHIFT ; 
 unsigned long SRMMU_NOCACHE_VADDR ; 
 int bit_map_string_get (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 TYPE_1__ srmmu_nocache_map ; 
 scalar_t__ srmmu_nocache_size ; 

__attribute__((used)) static unsigned long __srmmu_get_nocache(int size, int align)
{
	int offset;

	if (size < SRMMU_NOCACHE_BITMAP_SHIFT) {
		printk("Size 0x%x too small for nocache request\n", size);
		size = SRMMU_NOCACHE_BITMAP_SHIFT;
	}
	if (size & (SRMMU_NOCACHE_BITMAP_SHIFT-1)) {
		printk("Size 0x%x unaligned int nocache request\n", size);
		size += SRMMU_NOCACHE_BITMAP_SHIFT-1;
	}
	BUG_ON(align > SRMMU_NOCACHE_ALIGN_MAX);

	offset = bit_map_string_get(&srmmu_nocache_map,
		       			size >> SRMMU_NOCACHE_BITMAP_SHIFT,
					align >> SRMMU_NOCACHE_BITMAP_SHIFT);
	if (offset == -1) {
		printk("srmmu: out of nocache %d: %d/%d\n",
		    size, (int) srmmu_nocache_size,
		    srmmu_nocache_map.used << SRMMU_NOCACHE_BITMAP_SHIFT);
		return 0;
	}

	return (SRMMU_NOCACHE_VADDR + (offset << SRMMU_NOCACHE_BITMAP_SHIFT));
}