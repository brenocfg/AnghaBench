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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_VGACNTRL ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_device*) ; 
 int /*<<< orphan*/  VGACNTRL ; 
 int /*<<< orphan*/  VLV_VGACNTRL ; 

__attribute__((used)) static inline uint32_t i915_vgacntrl_reg(struct drm_device *dev)
{
	if (HAS_PCH_SPLIT(dev))
		return CPU_VGACNTRL;
	else if (IS_VALLEYVIEW(dev))
		return VLV_VGACNTRL;
	else
		return VGACNTRL;
}