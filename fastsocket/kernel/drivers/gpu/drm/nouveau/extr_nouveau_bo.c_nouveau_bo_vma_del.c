#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nouveau_vma {int /*<<< orphan*/  head; scalar_t__ node; } ;
struct TYPE_4__ {scalar_t__ mem_type; } ;
struct TYPE_6__ {TYPE_2__* bdev; TYPE_1__ mem; } ;
struct nouveau_bo {TYPE_3__ bo; } ;
struct TYPE_5__ {int /*<<< orphan*/  fence_lock; } ;

/* Variables and functions */
 scalar_t__ TTM_PL_SYSTEM ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_vm_put (struct nouveau_vma*) ; 
 int /*<<< orphan*/  nouveau_vm_unmap (struct nouveau_vma*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_wait (TYPE_3__*,int,int,int) ; 

void
nouveau_bo_vma_del(struct nouveau_bo *nvbo, struct nouveau_vma *vma)
{
	if (vma->node) {
		if (nvbo->bo.mem.mem_type != TTM_PL_SYSTEM) {
			spin_lock(&nvbo->bo.bdev->fence_lock);
			ttm_bo_wait(&nvbo->bo, false, false, false);
			spin_unlock(&nvbo->bo.bdev->fence_lock);
			nouveau_vm_unmap(vma);
		}

		nouveau_vm_put(vma);
		list_del(&vma->head);
	}
}