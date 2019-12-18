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
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 int /*<<< orphan*/  IS_I830 (struct drm_device*) ; 
 scalar_t__ IS_MOBILE (struct drm_device*) ; 

__attribute__((used)) static bool intel_lvds_supported(struct drm_device *dev)
{
	/* With the introduction of the PCH we gained a dedicated
	 * LVDS presence pin, use it. */
	if (HAS_PCH_SPLIT(dev))
		return true;

	/* Otherwise LVDS was only attached to mobile products,
	 * except for the inglorious 830gm */
	return IS_MOBILE(dev) && !IS_I830(dev);
}