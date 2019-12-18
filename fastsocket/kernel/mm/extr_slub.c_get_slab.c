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
struct kmem_cache {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int SLUB_DMA ; 
 struct kmem_cache* ZERO_SIZE_PTR ; 
 struct kmem_cache* dma_kmalloc_cache (int,int) ; 
 int fls (size_t) ; 
 struct kmem_cache* kmalloc_caches ; 
 int* size_index ; 
 size_t size_index_elem (size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct kmem_cache *get_slab(size_t size, gfp_t flags)
{
	int index;

	if (size <= 192) {
		if (!size)
			return ZERO_SIZE_PTR;

		index = size_index[size_index_elem(size)];
	} else
		index = fls(size - 1);

#ifdef CONFIG_ZONE_DMA
	if (unlikely((flags & SLUB_DMA)))
		return dma_kmalloc_cache(index, flags);

#endif
	return &kmalloc_caches[index];
}