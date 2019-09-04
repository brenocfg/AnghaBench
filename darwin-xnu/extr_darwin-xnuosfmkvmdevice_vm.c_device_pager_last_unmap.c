#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  memory_object_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* device_pager_t ;
typedef  void* boolean_t ;
struct TYPE_5__ {scalar_t__ ref_count; void* is_mapped; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 void* TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  device_pager_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_pager_lock (TYPE_1__*) ; 
 TYPE_1__* device_pager_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_pager_unlock (TYPE_1__*) ; 

kern_return_t
device_pager_last_unmap(
	memory_object_t	mem_obj)
{
	device_pager_t	device_object;
	boolean_t	drop_ref;

	device_object = device_pager_lookup(mem_obj);

	device_pager_lock(device_object);
	assert(device_object->ref_count > 0);
	if (device_object->is_mapped) {
		device_object->is_mapped = FALSE;
		drop_ref = TRUE;
	} else {
		drop_ref = FALSE;
	}
	device_pager_unlock(device_object);

	if (drop_ref) {
		device_pager_deallocate(mem_obj);
	}

	return KERN_SUCCESS;
}