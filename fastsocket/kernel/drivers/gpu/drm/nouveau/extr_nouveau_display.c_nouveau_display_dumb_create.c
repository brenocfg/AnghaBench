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
struct nouveau_bo {int /*<<< orphan*/  gem; } ;
struct drm_mode_create_dumb {int pitch; int width; int bpp; int size; int height; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOUVEAU_GEM_DOMAIN_VRAM ; 
 int PAGE_SIZE ; 
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (int /*<<< orphan*/ ) ; 
 int nouveau_gem_new (struct drm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nouveau_bo**) ; 
 void* roundup (int,int) ; 

int
nouveau_display_dumb_create(struct drm_file *file_priv, struct drm_device *dev,
			    struct drm_mode_create_dumb *args)
{
	struct nouveau_bo *bo;
	int ret;

	args->pitch = roundup(args->width * (args->bpp / 8), 256);
	args->size = args->pitch * args->height;
	args->size = roundup(args->size, PAGE_SIZE);

	ret = nouveau_gem_new(dev, args->size, 0, NOUVEAU_GEM_DOMAIN_VRAM, 0, 0, &bo);
	if (ret)
		return ret;

	ret = drm_gem_handle_create(file_priv, bo->gem, &args->handle);
	drm_gem_object_unreference_unlocked(bo->gem);
	return ret;
}