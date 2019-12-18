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
typedef  scalar_t__ u32 ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,scalar_t__) ; 
 scalar_t__ _intel_panel_get_max_backlight (struct drm_device*) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 

u32 intel_panel_get_max_backlight(struct drm_device *dev)
{
	u32 max;

	max = _intel_panel_get_max_backlight(dev);
	if (max == 0) {
		/* XXX add code here to query mode clock or hardware clock
		 * and program max PWM appropriately.
		 */
		pr_warn_once("fixme: max PWM is zero\n");
		return 1;
	}

	DRM_DEBUG_DRIVER("max backlight PWM = %d\n", max);
	return max;
}