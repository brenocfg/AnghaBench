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
struct nouveau_vma {int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm; } ;
struct nouveau_cli {TYPE_1__ base; } ;
struct nouveau_bo {int /*<<< orphan*/  bo; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct nouveau_vma*) ; 
 struct nouveau_vma* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nouveau_bo_vma_add (struct nouveau_bo*,int /*<<< orphan*/ ,struct nouveau_vma*) ; 
 struct nouveau_vma* nouveau_bo_vma_find (struct nouveau_bo*,int /*<<< orphan*/ ) ; 
 struct nouveau_cli* nouveau_cli (struct drm_file*) ; 
 struct nouveau_bo* nouveau_gem_object (struct drm_gem_object*) ; 
 int ttm_bo_reserve (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (int /*<<< orphan*/ *) ; 

int
nouveau_gem_object_open(struct drm_gem_object *gem, struct drm_file *file_priv)
{
	struct nouveau_cli *cli = nouveau_cli(file_priv);
	struct nouveau_bo *nvbo = nouveau_gem_object(gem);
	struct nouveau_vma *vma;
	int ret;

	if (!cli->base.vm)
		return 0;

	ret = ttm_bo_reserve(&nvbo->bo, false, false, false, 0);
	if (ret)
		return ret;

	vma = nouveau_bo_vma_find(nvbo, cli->base.vm);
	if (!vma) {
		vma = kzalloc(sizeof(*vma), GFP_KERNEL);
		if (!vma) {
			ret = -ENOMEM;
			goto out;
		}

		ret = nouveau_bo_vma_add(nvbo, cli->base.vm, vma);
		if (ret) {
			kfree(vma);
			goto out;
		}
	} else {
		vma->refcount++;
	}

out:
	ttm_bo_unreserve(&nvbo->bo);
	return ret;
}