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
typedef  int uint32_t ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKCFG ; 
#define  CLKCFG_FSB_1067 135 
#define  CLKCFG_FSB_1333 134 
#define  CLKCFG_FSB_1600 133 
#define  CLKCFG_FSB_1600_ALT 132 
#define  CLKCFG_FSB_400 131 
#define  CLKCFG_FSB_533 130 
#define  CLKCFG_FSB_667 129 
#define  CLKCFG_FSB_800 128 
 int CLKCFG_FSB_MASK ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_device*) ; 

__attribute__((used)) static int
intel_hrawclk(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	uint32_t clkcfg;

	/* There is no CLKCFG reg in Valleyview. VLV hrawclk is 200 MHz */
	if (IS_VALLEYVIEW(dev))
		return 200;

	clkcfg = I915_READ(CLKCFG);
	switch (clkcfg & CLKCFG_FSB_MASK) {
	case CLKCFG_FSB_400:
		return 100;
	case CLKCFG_FSB_533:
		return 133;
	case CLKCFG_FSB_667:
		return 166;
	case CLKCFG_FSB_800:
		return 200;
	case CLKCFG_FSB_1067:
		return 266;
	case CLKCFG_FSB_1333:
		return 333;
	/* these two are just a guess; one of them might be right */
	case CLKCFG_FSB_1600:
	case CLKCFG_FSB_1600_ALT:
		return 400;
	default:
		return 133;
	}
}