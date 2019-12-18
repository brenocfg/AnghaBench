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
struct ttm_mem_type_manager {struct nouveau_vm* priv; int /*<<< orphan*/  bdev; } ;
struct nv04_vmmgr_priv {int /*<<< orphan*/  vm; } ;
struct nouveau_vmmgr {int dummy; } ;
struct nouveau_vm {int dummy; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_vm_ref (int /*<<< orphan*/ ,struct nouveau_vm**,int /*<<< orphan*/ *) ; 
 struct nouveau_vmmgr* nouveau_vmmgr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv04_gart_manager_init(struct ttm_mem_type_manager *man, unsigned long psize)
{
	struct nouveau_drm *drm = nouveau_bdev(man->bdev);
	struct nouveau_vmmgr *vmm = nouveau_vmmgr(drm->device);
	struct nv04_vmmgr_priv *priv = (void *)vmm;
	struct nouveau_vm *vm = NULL;
	nouveau_vm_ref(priv->vm, &vm, NULL);
	man->priv = vm;
	return 0;
}