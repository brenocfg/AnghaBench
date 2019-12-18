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
struct page {struct kmem_cache* slab; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_valid_pointer (struct kmem_cache*,struct page*,void const*) ; 
 struct page* get_object_page (void const*) ; 

int kmem_ptr_validate(struct kmem_cache *s, const void *object)
{
	struct page *page;

	page = get_object_page(object);

	if (!page || s != page->slab)
		/* No slab or wrong slab */
		return 0;

	if (!check_valid_pointer(s, page, object))
		return 0;

	/*
	 * We could also check if the object is on the slabs freelist.
	 * But this would be too expensive and it seems that the main
	 * purpose of kmem_ptr_valid() is to check if the object belongs
	 * to a certain slab.
	 */
	return 1;
}