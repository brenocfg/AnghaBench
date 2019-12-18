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
typedef  int /*<<< orphan*/  u32 ;
struct sg_table {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {TYPE_1__ mem; } ;
struct nouveau_bo {struct drm_gem_object* gem; TYPE_2__ bo; int /*<<< orphan*/  valid_domains; } ;
struct drm_gem_object {struct nouveau_bo* driver_private; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_gem_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  NOUVEAU_GEM_DOMAIN_GART ; 
 int /*<<< orphan*/  TTM_PL_FLAG_TT ; 
 struct drm_gem_object* drm_gem_object_alloc (struct drm_device*,int /*<<< orphan*/ ) ; 
 int nouveau_bo_new (struct drm_device*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sg_table*,struct nouveau_bo**) ; 
 int /*<<< orphan*/  nouveau_bo_ref (int /*<<< orphan*/ *,struct nouveau_bo**) ; 

struct drm_gem_object *nouveau_gem_prime_import_sg_table(struct drm_device *dev,
							 size_t size,
							 struct sg_table *sg)
{
	struct nouveau_bo *nvbo;
	u32 flags = 0;
	int ret;

	flags = TTM_PL_FLAG_TT;

	ret = nouveau_bo_new(dev, size, 0, flags, 0, 0,
			     sg, &nvbo);
	if (ret)
		return ERR_PTR(ret);

	nvbo->valid_domains = NOUVEAU_GEM_DOMAIN_GART;
	nvbo->gem = drm_gem_object_alloc(dev, nvbo->bo.mem.size);
	if (!nvbo->gem) {
		nouveau_bo_ref(NULL, &nvbo);
		return ERR_PTR(-ENOMEM);
	}

	nvbo->gem->driver_private = nvbo;
	return nvbo->gem;
}