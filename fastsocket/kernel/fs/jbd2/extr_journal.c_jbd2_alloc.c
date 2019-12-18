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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned long) ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  __GFP_REPEAT ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int) ; 
 int get_order (size_t) ; 
 int /*<<< orphan*/  get_slab (size_t) ; 
 void* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* vmalloc (size_t) ; 

void *jbd2_alloc(size_t size, gfp_t flags)
{
	void *ptr;

	BUG_ON(size & (size-1)); /* Must be a power of 2 */

	flags |= __GFP_REPEAT;
	if (size == PAGE_SIZE)
		ptr = (void *)__get_free_pages(flags, 0);
	else if (size > PAGE_SIZE) {
		int order = get_order(size);

		if (order < 3)
			ptr = (void *)__get_free_pages(flags, order);
		else
			ptr = vmalloc(size);
	} else
		ptr = kmem_cache_alloc(get_slab(size), flags);

	/* Check alignment; SLUB has gotten this wrong in the past,
	 * and this can lead to user data corruption! */
	BUG_ON(((unsigned long) ptr) & (size-1));

	return ptr;
}