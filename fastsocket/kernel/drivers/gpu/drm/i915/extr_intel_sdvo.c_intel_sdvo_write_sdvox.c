#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct intel_sdvo {scalar_t__ sdvo_reg; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_READ (scalar_t__) ; 
 int /*<<< orphan*/  I915_WRITE (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PCH_SDVOB ; 
 scalar_t__ SDVOB ; 
 scalar_t__ SDVOC ; 

__attribute__((used)) static void intel_sdvo_write_sdvox(struct intel_sdvo *intel_sdvo, u32 val)
{
	struct drm_device *dev = intel_sdvo->base.base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 bval = val, cval = val;
	int i;

	if (intel_sdvo->sdvo_reg == PCH_SDVOB) {
		I915_WRITE(intel_sdvo->sdvo_reg, val);
		I915_READ(intel_sdvo->sdvo_reg);
		return;
	}

	if (intel_sdvo->sdvo_reg == SDVOB) {
		cval = I915_READ(SDVOC);
	} else {
		bval = I915_READ(SDVOB);
	}
	/*
	 * Write the registers twice for luck. Sometimes,
	 * writing them only once doesn't appear to 'stick'.
	 * The BIOS does this too. Yay, magic
	 */
	for (i = 0; i < 2; i++)
	{
		I915_WRITE(SDVOB, bval);
		I915_READ(SDVOB);
		I915_WRITE(SDVOC, cval);
		I915_READ(SDVOC);
	}
}