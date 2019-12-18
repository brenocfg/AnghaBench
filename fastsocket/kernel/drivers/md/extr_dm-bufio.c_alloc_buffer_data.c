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
struct dm_bufio_client {scalar_t__ block_size; int /*<<< orphan*/  pages_per_block_bits; } ;
typedef  int gfp_t ;
typedef  enum data_mode { ____Placeholder_data_mode } data_mode ;
struct TYPE_2__ {unsigned int flags; } ;

/* Variables and functions */
 int DATA_MODE_GET_FREE_PAGES ; 
 int DATA_MODE_SLAB ; 
 int DATA_MODE_VMALLOC ; 
 scalar_t__ DM_BUFIO_BLOCK_SIZE_GFP_LIMIT ; 
 scalar_t__ DM_BUFIO_BLOCK_SIZE_SLAB_LIMIT ; 
 int /*<<< orphan*/  DM_BUFIO_CACHE (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned int PF_MEMALLOC ; 
 int __GFP_HIGHMEM ; 
 int __GFP_NORETRY ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 void* __vmalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 void* kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *alloc_buffer_data(struct dm_bufio_client *c, gfp_t gfp_mask,
			       enum data_mode *data_mode)
{
	unsigned memalloc_flag;
	void *ptr;

	if (c->block_size <= DM_BUFIO_BLOCK_SIZE_SLAB_LIMIT) {
		*data_mode = DATA_MODE_SLAB;
		return kmem_cache_alloc(DM_BUFIO_CACHE(c), gfp_mask);
	}

	if (c->block_size <= DM_BUFIO_BLOCK_SIZE_GFP_LIMIT &&
	    gfp_mask & __GFP_NORETRY) {
		*data_mode = DATA_MODE_GET_FREE_PAGES;
		return (void *)__get_free_pages(gfp_mask,
						c->pages_per_block_bits);
	}

	*data_mode = DATA_MODE_VMALLOC;

	/*
	 * __vmalloc allocates the data pages and auxiliary structures with
	 * gfp_flags that were specified, but pagetables are always allocated
	 * with GFP_KERNEL, no matter what was specified as gfp_mask.
	 *
	 * Consequently, we must set per-process flag PF_MEMALLOC_NOIO so that
	 * all allocations done by this process (including pagetables) are done
	 * as if GFP_NOIO was specified.
	 */

	if (gfp_mask & __GFP_NORETRY) {
		memalloc_flag = current->flags & PF_MEMALLOC;
		current->flags |= PF_MEMALLOC;
	}

	ptr = __vmalloc(c->block_size, gfp_mask | __GFP_HIGHMEM, PAGE_KERNEL);

	if (gfp_mask & __GFP_NORETRY)
		current->flags = (current->flags & ~PF_MEMALLOC) | memalloc_flag;

	return ptr;
}