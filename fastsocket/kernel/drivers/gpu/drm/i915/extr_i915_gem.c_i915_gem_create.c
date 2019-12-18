#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int drm_gem_handle_create (struct drm_file*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_release (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (TYPE_1__*) ; 
 struct drm_i915_gem_object* i915_gem_alloc_object (struct drm_device*,scalar_t__) ; 
 int /*<<< orphan*/  i915_gem_info_remove_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_free (struct drm_i915_gem_object*) ; 
 scalar_t__ roundup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_i915_gem_object_create (struct drm_i915_gem_object*) ; 

__attribute__((used)) static int
i915_gem_create(struct drm_file *file,
		struct drm_device *dev,
		uint64_t size,
		uint32_t *handle_p)
{
	struct drm_i915_gem_object *obj;
	int ret;
	u32 handle;

	size = roundup(size, PAGE_SIZE);
	if (size == 0)
		return -EINVAL;

	/* Allocate the new object */
	obj = i915_gem_alloc_object(dev, size);
	if (obj == NULL)
		return -ENOMEM;

	ret = drm_gem_handle_create(file, &obj->base, &handle);
	if (ret) {
		drm_gem_object_release(&obj->base);
		i915_gem_info_remove_obj(dev->dev_private, obj->base.size);
		i915_gem_object_free(obj);
		return ret;
	}

	/* drop reference from allocate - handle holds it now */
	drm_gem_object_unreference(&obj->base);
	trace_i915_gem_object_create(obj);

	*handle_p = handle;
	return 0;
}