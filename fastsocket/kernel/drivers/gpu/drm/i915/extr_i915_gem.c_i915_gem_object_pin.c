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
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  aliasing_ppgtt; } ;
struct drm_i915_private {TYPE_3__ mm; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct drm_i915_gem_object {scalar_t__ pin_count; int gtt_offset; int pin_mappable; int /*<<< orphan*/  cache_level; int /*<<< orphan*/  has_global_gtt_mapping; TYPE_2__ base; int /*<<< orphan*/ * gtt_space; int /*<<< orphan*/  map_and_fenceable; } ;
struct TYPE_4__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ DRM_I915_GEM_OBJECT_MAX_PIN_COUNT ; 
 int EBUSY ; 
 int /*<<< orphan*/  WARN (scalar_t__,char*,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  i915_gem_gtt_bind_object (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int i915_gem_object_bind_to_gtt (struct drm_i915_gem_object*,int,int,int) ; 
 int i915_gem_object_unbind (struct drm_i915_gem_object*) ; 

int
i915_gem_object_pin(struct drm_i915_gem_object *obj,
		    uint32_t alignment,
		    bool map_and_fenceable,
		    bool nonblocking)
{
	int ret;

	if (WARN_ON(obj->pin_count == DRM_I915_GEM_OBJECT_MAX_PIN_COUNT))
		return -EBUSY;

	if (obj->gtt_space != NULL) {
		if ((alignment && obj->gtt_offset & (alignment - 1)) ||
		    (map_and_fenceable && !obj->map_and_fenceable)) {
			WARN(obj->pin_count,
			     "bo is already pinned with incorrect alignment:"
			     " offset=%x, req.alignment=%x, req.map_and_fenceable=%d,"
			     " obj->map_and_fenceable=%d\n",
			     obj->gtt_offset, alignment,
			     map_and_fenceable,
			     obj->map_and_fenceable);
			ret = i915_gem_object_unbind(obj);
			if (ret)
				return ret;
		}
	}

	if (obj->gtt_space == NULL) {
		struct drm_i915_private *dev_priv = obj->base.dev->dev_private;

		ret = i915_gem_object_bind_to_gtt(obj, alignment,
						  map_and_fenceable,
						  nonblocking);
		if (ret)
			return ret;

		if (!dev_priv->mm.aliasing_ppgtt)
			i915_gem_gtt_bind_object(obj, obj->cache_level);
	}

	if (!obj->has_global_gtt_mapping && map_and_fenceable)
		i915_gem_gtt_bind_object(obj, obj->cache_level);

	obj->pin_count++;
	obj->pin_mappable |= map_and_fenceable;

	return 0;
}