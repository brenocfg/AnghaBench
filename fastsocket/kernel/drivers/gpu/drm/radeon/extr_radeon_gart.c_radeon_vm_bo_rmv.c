#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct radeon_device {TYPE_1__ vm_manager; } ;
struct radeon_bo_va {int /*<<< orphan*/  bo_list; TYPE_2__* vm; int /*<<< orphan*/  vm_list; int /*<<< orphan*/  bo; scalar_t__ soffset; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct radeon_bo_va*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int radeon_vm_bo_update_pte (struct radeon_device*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int radeon_vm_bo_rmv(struct radeon_device *rdev,
		     struct radeon_bo_va *bo_va)
{
	int r = 0;

	mutex_lock(&rdev->vm_manager.lock);
	mutex_lock(&bo_va->vm->mutex);
	if (bo_va->soffset) {
		r = radeon_vm_bo_update_pte(rdev, bo_va->vm, bo_va->bo, NULL);
	}
	mutex_unlock(&rdev->vm_manager.lock);
	list_del(&bo_va->vm_list);
	mutex_unlock(&bo_va->vm->mutex);
	list_del(&bo_va->bo_list);

	kfree(bo_va);
	return r;
}