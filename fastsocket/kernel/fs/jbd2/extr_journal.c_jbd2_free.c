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
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int get_order (size_t) ; 
 int /*<<< orphan*/  get_slab (size_t) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vfree (void*) ; 

void jbd2_free(void *ptr, size_t size)
{
	if (size == PAGE_SIZE) {
		free_pages((unsigned long)ptr, 0);
		return;
	}
	if (size > PAGE_SIZE) {
		int order = get_order(size);

		if (order < 3)
			free_pages((unsigned long)ptr, order);
		else
			vfree(ptr);
		return;
	}
	kmem_cache_free(get_slab(size), ptr);
}