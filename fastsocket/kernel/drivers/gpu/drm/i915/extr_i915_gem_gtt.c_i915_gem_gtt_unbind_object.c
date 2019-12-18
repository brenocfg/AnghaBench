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
struct TYPE_4__ {int /*<<< orphan*/  (* gtt_clear_range ) (struct drm_device*,int,int) ;} ;
struct drm_i915_private {TYPE_1__ gtt; } ;
struct TYPE_6__ {int size; struct drm_device* dev; } ;
struct drm_i915_gem_object {scalar_t__ has_global_gtt_mapping; TYPE_3__ base; TYPE_2__* gtt_space; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_5__ {int start; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  stub1 (struct drm_device*,int,int) ; 

void i915_gem_gtt_unbind_object(struct drm_i915_gem_object *obj)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;

	dev_priv->gtt.gtt_clear_range(obj->base.dev,
				      obj->gtt_space->start >> PAGE_SHIFT,
				      obj->base.size >> PAGE_SHIFT);

	obj->has_global_gtt_mapping = 0;
}