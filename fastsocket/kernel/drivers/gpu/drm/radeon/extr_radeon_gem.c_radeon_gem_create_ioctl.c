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
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_device {int /*<<< orphan*/  exclusive_lock; } ;
struct drm_radeon_gem_create {int /*<<< orphan*/  handle; int /*<<< orphan*/  initial_domain; int /*<<< orphan*/  alignment; int /*<<< orphan*/  size; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int drm_gem_handle_create (struct drm_file*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (struct drm_gem_object*) ; 
 int radeon_gem_handle_lockup (struct radeon_device*,int) ; 
 int radeon_gem_object_create (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct drm_gem_object**) ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int radeon_gem_create_ioctl(struct drm_device *dev, void *data,
			    struct drm_file *filp)
{
	struct radeon_device *rdev = dev->dev_private;
	struct drm_radeon_gem_create *args = data;
	struct drm_gem_object *gobj;
	uint32_t handle;
	int r;

	down_read(&rdev->exclusive_lock);
	/* create a gem object to contain this object in */
	args->size = roundup(args->size, PAGE_SIZE);
	r = radeon_gem_object_create(rdev, args->size, args->alignment,
					args->initial_domain, false,
					false, &gobj);
	if (r) {
		up_read(&rdev->exclusive_lock);
		r = radeon_gem_handle_lockup(rdev, r);
		return r;
	}
	r = drm_gem_handle_create(filp, gobj, &handle);
	/* drop reference from allocate - handle holds it now */
	drm_gem_object_unreference_unlocked(gobj);
	if (r) {
		up_read(&rdev->exclusive_lock);
		r = radeon_gem_handle_lockup(rdev, r);
		return r;
	}
	args->handle = handle;
	up_read(&rdev->exclusive_lock);
	return 0;
}