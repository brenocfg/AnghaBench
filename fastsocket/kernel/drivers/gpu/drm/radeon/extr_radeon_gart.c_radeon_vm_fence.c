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
struct radeon_vm {size_t id; void* fence; } ;
struct radeon_fence {int dummy; } ;
struct TYPE_2__ {void** active; } ;
struct radeon_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 void* radeon_fence_ref (struct radeon_fence*) ; 
 int /*<<< orphan*/  radeon_fence_unref (void**) ; 

void radeon_vm_fence(struct radeon_device *rdev,
		     struct radeon_vm *vm,
		     struct radeon_fence *fence)
{
	radeon_fence_unref(&rdev->vm_manager.active[vm->id]);
	rdev->vm_manager.active[vm->id] = radeon_fence_ref(fence);

	radeon_fence_unref(&vm->fence);
	vm->fence = radeon_fence_ref(fence);
}