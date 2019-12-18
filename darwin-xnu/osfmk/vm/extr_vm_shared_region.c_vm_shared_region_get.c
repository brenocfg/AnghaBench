#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_shared_region_t ;
typedef  TYPE_1__* task_t ;
struct TYPE_9__ {scalar_t__ sr_ref_count; struct TYPE_9__* shared_region; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHARED_REGION_TRACE_DEBUG (char*) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_shared_region_lock () ; 
 int /*<<< orphan*/  vm_shared_region_reference_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_shared_region_unlock () ; 

vm_shared_region_t
vm_shared_region_get(
	task_t		task)
{
	vm_shared_region_t	shared_region;

	SHARED_REGION_TRACE_DEBUG(
		("shared_region: -> get(%p)\n",
		 (void *)VM_KERNEL_ADDRPERM(task)));

	task_lock(task);
	vm_shared_region_lock();
	shared_region = task->shared_region;
	if (shared_region) {
		assert(shared_region->sr_ref_count > 0);
		vm_shared_region_reference_locked(shared_region);
	}
	vm_shared_region_unlock();
	task_unlock(task);

	SHARED_REGION_TRACE_DEBUG(
		("shared_region: get(%p) <- %p\n",
		 (void *)VM_KERNEL_ADDRPERM(task),
		 (void *)VM_KERNEL_ADDRPERM(shared_region)));

	return shared_region;
}