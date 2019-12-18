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
struct drm_file {int dummy; } ;
struct drm_device {TYPE_3__* dev_private; } ;
struct TYPE_5__ {int param; int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ drm_i915_setparam_t ;
struct TYPE_4__ {int allow_batchbuffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  fence_reg_start; int /*<<< orphan*/  num_fence_regs; TYPE_1__ dri1; } ;
typedef  TYPE_3__ drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
#define  I915_SETPARAM_ALLOW_BATCHBUFFER 131 
#define  I915_SETPARAM_NUM_USED_FENCES 130 
#define  I915_SETPARAM_TEX_LRU_LOG_GRANULARITY 129 
#define  I915_SETPARAM_USE_MI_BATCHBUFFER_START 128 

__attribute__((used)) static int i915_setparam(struct drm_device *dev, void *data,
			 struct drm_file *file_priv)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	drm_i915_setparam_t *param = data;

	if (!dev_priv) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}

	switch (param->param) {
	case I915_SETPARAM_USE_MI_BATCHBUFFER_START:
		break;
	case I915_SETPARAM_TEX_LRU_LOG_GRANULARITY:
		break;
	case I915_SETPARAM_ALLOW_BATCHBUFFER:
		dev_priv->dri1.allow_batchbuffer = param->value ? 1 : 0;
		break;
	case I915_SETPARAM_NUM_USED_FENCES:
		if (param->value > dev_priv->num_fence_regs ||
		    param->value < 0)
			return -EINVAL;
		/* Userspace can use first N regs */
		dev_priv->fence_reg_start = param->value;
		break;
	default:
		DRM_DEBUG_DRIVER("unknown parameter %d\n",
					param->param);
		return -EINVAL;
	}

	return 0;
}