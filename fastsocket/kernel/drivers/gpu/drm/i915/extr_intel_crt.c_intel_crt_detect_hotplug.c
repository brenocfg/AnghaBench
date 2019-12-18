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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 int CRT_HOTPLUG_FORCE_DETECT ; 
 int CRT_HOTPLUG_INT_STATUS ; 
 int CRT_HOTPLUG_MONITOR_MASK ; 
 int CRT_HOTPLUG_MONITOR_NONE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_G4X (struct drm_device*) ; 
 int /*<<< orphan*/  IS_GM45 (struct drm_device*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_device*) ; 
 int /*<<< orphan*/  PORT_HOTPLUG_EN ; 
 int /*<<< orphan*/  PORT_HOTPLUG_STAT ; 
 int intel_ironlake_crt_detect_hotplug (struct drm_connector*) ; 
 int valleyview_crt_detect_hotplug (struct drm_connector*) ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static bool intel_crt_detect_hotplug(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 hotplug_en, orig, stat;
	bool ret = false;
	int i, tries = 0;

	if (HAS_PCH_SPLIT(dev))
		return intel_ironlake_crt_detect_hotplug(connector);

	if (IS_VALLEYVIEW(dev))
		return valleyview_crt_detect_hotplug(connector);

	/*
	 * On 4 series desktop, CRT detect sequence need to be done twice
	 * to get a reliable result.
	 */

	if (IS_G4X(dev) && !IS_GM45(dev))
		tries = 2;
	else
		tries = 1;
	hotplug_en = orig = I915_READ(PORT_HOTPLUG_EN);
	hotplug_en |= CRT_HOTPLUG_FORCE_DETECT;

	for (i = 0; i < tries ; i++) {
		/* turn on the FORCE_DETECT */
		I915_WRITE(PORT_HOTPLUG_EN, hotplug_en);
		/* wait for FORCE_DETECT to go off */
		if (wait_for((I915_READ(PORT_HOTPLUG_EN) &
			      CRT_HOTPLUG_FORCE_DETECT) == 0,
			     1000))
			DRM_DEBUG_KMS("timed out waiting for FORCE_DETECT to go off");
	}

	stat = I915_READ(PORT_HOTPLUG_STAT);
	if ((stat & CRT_HOTPLUG_MONITOR_MASK) != CRT_HOTPLUG_MONITOR_NONE)
		ret = true;

	/* clear the interrupt we just generated, if any */
	I915_WRITE(PORT_HOTPLUG_STAT, CRT_HOTPLUG_INT_STATUS);

	/* and put the bits back */
	I915_WRITE(PORT_HOTPLUG_EN, orig);

	return ret;
}