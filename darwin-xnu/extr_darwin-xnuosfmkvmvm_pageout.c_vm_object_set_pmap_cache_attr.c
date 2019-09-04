#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  int /*<<< orphan*/  upl_page_info_array_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {unsigned int wimg_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_BATCH_SET_CACHE_ATTR (TYPE_1__*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int VM_WIMG_MASK ; 
 unsigned int VM_WIMG_USE_DEFAULT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
vm_object_set_pmap_cache_attr(
		vm_object_t		object,
		upl_page_info_array_t	user_page_list,
		unsigned int		num_pages,
		boolean_t		batch_pmap_op)
{
	unsigned int    cache_attr = 0;

	cache_attr = object->wimg_bits & VM_WIMG_MASK;
	assert(user_page_list);
	if (cache_attr != VM_WIMG_USE_DEFAULT) {
		PMAP_BATCH_SET_CACHE_ATTR(object, user_page_list, cache_attr, num_pages, batch_pmap_op);
	}
}