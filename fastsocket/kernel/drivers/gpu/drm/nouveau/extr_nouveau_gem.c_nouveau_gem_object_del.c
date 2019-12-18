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
struct ttm_buffer_object {int /*<<< orphan*/  sg; } ;
struct nouveau_bo {int pin_refcnt; struct ttm_buffer_object bo; int /*<<< orphan*/ * gem; } ;
struct drm_gem_object {scalar_t__ import_attach; struct nouveau_bo* driver_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_gem_object*) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (struct nouveau_bo*) ; 
 int /*<<< orphan*/  ttm_bo_unref (struct ttm_buffer_object**) ; 
 scalar_t__ unlikely (int) ; 

void
nouveau_gem_object_del(struct drm_gem_object *gem)
{
	struct nouveau_bo *nvbo = gem->driver_private;
	struct ttm_buffer_object *bo = &nvbo->bo;

	if (!nvbo)
		return;
	nvbo->gem = NULL;

	if (unlikely(nvbo->pin_refcnt)) {
		nvbo->pin_refcnt = 1;
		nouveau_bo_unpin(nvbo);
	}

	if (gem->import_attach)
		drm_prime_gem_destroy(gem, nvbo->bo.sg);

	ttm_bo_unref(&bo);

	drm_gem_object_release(gem);
	kfree(gem);
}