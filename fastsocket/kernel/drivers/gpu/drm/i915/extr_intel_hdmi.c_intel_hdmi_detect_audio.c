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
struct intel_hdmi {int /*<<< orphan*/  ddc_bus; } ;
struct edid {int input; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector {TYPE_1__* dev; } ;
struct TYPE_2__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int DRM_EDID_INPUT_DIGITAL ; 
 int drm_detect_monitor_audio (struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ ) ; 
 struct intel_hdmi* intel_attached_hdmi (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_gmbus_get_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static bool
intel_hdmi_detect_audio(struct drm_connector *connector)
{
	struct intel_hdmi *intel_hdmi = intel_attached_hdmi(connector);
	struct drm_i915_private *dev_priv = connector->dev->dev_private;
	struct edid *edid;
	bool has_audio = false;

	edid = drm_get_edid(connector,
			    intel_gmbus_get_adapter(dev_priv,
						    intel_hdmi->ddc_bus));
	if (edid) {
		if (edid->input & DRM_EDID_INPUT_DIGITAL)
			has_audio = drm_detect_monitor_audio(edid);
		kfree(edid);
	}

	return has_audio;
}