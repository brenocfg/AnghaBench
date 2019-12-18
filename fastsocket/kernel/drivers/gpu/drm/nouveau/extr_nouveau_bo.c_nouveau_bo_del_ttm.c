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
struct ttm_buffer_object {int /*<<< orphan*/  bdev; } ;
struct nouveau_drm {struct drm_device* dev; } ;
struct nouveau_bo {int /*<<< orphan*/  tile; int /*<<< orphan*/  gem; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  kfree (struct nouveau_bo*) ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 struct nouveau_bo* nouveau_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  nv10_bo_put_tile_region (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nouveau_bo_del_ttm(struct ttm_buffer_object *bo)
{
	struct nouveau_drm *drm = nouveau_bdev(bo->bdev);
	struct drm_device *dev = drm->dev;
	struct nouveau_bo *nvbo = nouveau_bo(bo);

	if (unlikely(nvbo->gem))
		DRM_ERROR("bo %p still attached to GEM object\n", bo);
	nv10_bo_put_tile_region(dev, nvbo->tile, NULL);
	kfree(nvbo);
}