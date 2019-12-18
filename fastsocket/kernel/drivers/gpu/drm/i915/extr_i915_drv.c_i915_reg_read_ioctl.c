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
struct register_whitelist {scalar_t__ offset; int gen_bitmask; int size; } ;
struct drm_i915_reg_read {scalar_t__ offset; int /*<<< orphan*/  val; } ;
struct drm_i915_private {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct register_whitelist*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  I915_READ (scalar_t__) ; 
 int /*<<< orphan*/  I915_READ16 (scalar_t__) ; 
 int /*<<< orphan*/  I915_READ64 (scalar_t__) ; 
 int /*<<< orphan*/  I915_READ8 (scalar_t__) ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct register_whitelist* whitelist ; 

int i915_reg_read_ioctl(struct drm_device *dev,
			void *data, struct drm_file *file)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_reg_read *reg = data;
	struct register_whitelist const *entry = whitelist;
	int i;

	for (i = 0; i < ARRAY_SIZE(whitelist); i++, entry++) {
		if (entry->offset == reg->offset &&
		    (1 << INTEL_INFO(dev)->gen & entry->gen_bitmask))
			break;
	}

	if (i == ARRAY_SIZE(whitelist))
		return -EINVAL;

	switch (entry->size) {
	case 8:
		reg->val = I915_READ64(reg->offset);
		break;
	case 4:
		reg->val = I915_READ(reg->offset);
		break;
	case 2:
		reg->val = I915_READ16(reg->offset);
		break;
	case 1:
		reg->val = I915_READ8(reg->offset);
		break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	return 0;
}