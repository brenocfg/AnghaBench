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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct intel_sdvo {TYPE_2__ base; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  hotplug ;

/* Variables and functions */
 scalar_t__ IS_I945G (struct drm_device*) ; 
 scalar_t__ IS_I945GM (struct drm_device*) ; 
 int /*<<< orphan*/  SDVO_CMD_GET_HOT_PLUG_SUPPORT ; 
 int /*<<< orphan*/  intel_sdvo_get_value (struct intel_sdvo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint16_t intel_sdvo_get_hotplug_support(struct intel_sdvo *intel_sdvo)
{
	struct drm_device *dev = intel_sdvo->base.base.dev;
	uint16_t hotplug;

	/* HW Erratum: SDVO Hotplug is broken on all i945G chips, there's noise
	 * on the line. */
	if (IS_I945G(dev) || IS_I945GM(dev))
		return 0;

	if (!intel_sdvo_get_value(intel_sdvo, SDVO_CMD_GET_HOT_PLUG_SUPPORT,
					&hotplug, sizeof(hotplug)))
		return 0;

	return hotplug;
}