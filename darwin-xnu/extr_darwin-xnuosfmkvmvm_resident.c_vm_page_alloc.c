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
typedef  scalar_t__ vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;

/* Variables and functions */
 scalar_t__ VM_PAGE_NULL ; 
 int /*<<< orphan*/  vm_object_lock_assert_exclusive (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_grab_options (int) ; 
 int /*<<< orphan*/  vm_page_insert (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vm_page_t
vm_page_alloc(
	vm_object_t		object,
	vm_object_offset_t	offset)
{
	vm_page_t	mem;
	int		grab_options;

	vm_object_lock_assert_exclusive(object);
	grab_options = 0;
#if CONFIG_SECLUDED_MEMORY
	if (object->can_grab_secluded) {
		grab_options |= VM_PAGE_GRAB_SECLUDED;
	}
#endif /* CONFIG_SECLUDED_MEMORY */
	mem = vm_page_grab_options(grab_options);
	if (mem == VM_PAGE_NULL)
		return VM_PAGE_NULL;

	vm_page_insert(mem, object, offset);

	return(mem);
}