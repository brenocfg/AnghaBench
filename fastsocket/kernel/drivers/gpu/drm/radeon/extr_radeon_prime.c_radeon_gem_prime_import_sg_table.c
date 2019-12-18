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
struct sg_table {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  objects; } ;
struct radeon_device {TYPE_1__ gem; } ;
struct drm_gem_object {struct radeon_bo* driver_private; } ;
struct radeon_bo {struct drm_gem_object gem_base; int /*<<< orphan*/  list; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 struct drm_gem_object* ERR_PTR (int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_GTT ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int radeon_bo_create (struct radeon_device*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sg_table*,struct radeon_bo**) ; 

struct drm_gem_object *radeon_gem_prime_import_sg_table(struct drm_device *dev,
							size_t size,
							struct sg_table *sg)
{
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_bo *bo;
	int ret;

	ret = radeon_bo_create(rdev, size, PAGE_SIZE, false,
			       RADEON_GEM_DOMAIN_GTT, sg, &bo);
	if (ret)
		return ERR_PTR(ret);
	bo->gem_base.driver_private = bo;

	mutex_lock(&rdev->gem.mutex);
	list_add_tail(&bo->list, &rdev->gem.objects);
	mutex_unlock(&rdev->gem.mutex);

	return &bo->gem_base;
}