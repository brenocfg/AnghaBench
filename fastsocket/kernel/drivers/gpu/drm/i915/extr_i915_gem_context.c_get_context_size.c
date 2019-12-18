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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CXT_SIZE ; 
 int GEN6_CXT_TOTAL_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN7_CXT_SIZE ; 
 int GEN7_CXT_TOTAL_SIZE (int /*<<< orphan*/ ) ; 
 int HSW_CXT_TOTAL_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  IS_HASWELL (struct drm_device*) ; 

__attribute__((used)) static int get_context_size(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;
	u32 reg;

	switch (INTEL_INFO(dev)->gen) {
	case 6:
		reg = I915_READ(CXT_SIZE);
		ret = GEN6_CXT_TOTAL_SIZE(reg) * 64;
		break;
	case 7:
		reg = I915_READ(GEN7_CXT_SIZE);
		if (IS_HASWELL(dev))
			ret = HSW_CXT_TOTAL_SIZE(reg) * 64;
		else
			ret = GEN7_CXT_TOTAL_SIZE(reg) * 64;
		break;
	default:
		BUG();
	}

	return ret;
}