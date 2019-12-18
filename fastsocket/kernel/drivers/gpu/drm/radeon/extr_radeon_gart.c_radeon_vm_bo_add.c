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
struct radeon_vm {int /*<<< orphan*/  mutex; int /*<<< orphan*/  va; } ;
struct radeon_device {int dummy; } ;
struct radeon_bo_va {int valid; int ref_count; int /*<<< orphan*/  bo_list; int /*<<< orphan*/  vm_list; scalar_t__ flags; scalar_t__ eoffset; scalar_t__ soffset; struct radeon_bo* bo; struct radeon_vm* vm; } ;
struct radeon_bo {int /*<<< orphan*/  va; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct radeon_bo_va* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct radeon_bo_va *radeon_vm_bo_add(struct radeon_device *rdev,
				      struct radeon_vm *vm,
				      struct radeon_bo *bo)
{
	struct radeon_bo_va *bo_va;

	bo_va = kzalloc(sizeof(struct radeon_bo_va), GFP_KERNEL);
	if (bo_va == NULL) {
		return NULL;
	}
	bo_va->vm = vm;
	bo_va->bo = bo;
	bo_va->soffset = 0;
	bo_va->eoffset = 0;
	bo_va->flags = 0;
	bo_va->valid = false;
	bo_va->ref_count = 1;
	INIT_LIST_HEAD(&bo_va->bo_list);
	INIT_LIST_HEAD(&bo_va->vm_list);

	mutex_lock(&vm->mutex);
	list_add(&bo_va->vm_list, &vm->va);
	list_add_tail(&bo_va->bo_list, &bo->va);
	mutex_unlock(&vm->mutex);

	return bo_va;
}