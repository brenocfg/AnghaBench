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
struct TYPE_5__ {int /*<<< orphan*/  (* gtt_insert_entries ) (struct drm_device*,int /*<<< orphan*/ ,int,int) ;} ;
struct drm_i915_private {TYPE_2__ gtt; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct drm_i915_gem_object {int has_global_gtt_mapping; TYPE_3__* gtt_space; int /*<<< orphan*/  pages; TYPE_1__ base; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
typedef  enum i915_cache_level { ____Placeholder_i915_cache_level } i915_cache_level ;
struct TYPE_6__ {int start; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  stub1 (struct drm_device*,int /*<<< orphan*/ ,int,int) ; 

void i915_gem_gtt_bind_object(struct drm_i915_gem_object *obj,
			      enum i915_cache_level cache_level)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;

	dev_priv->gtt.gtt_insert_entries(dev, obj->pages,
					 obj->gtt_space->start >> PAGE_SHIFT,
					 cache_level);

	obj->has_global_gtt_mapping = 1;
}