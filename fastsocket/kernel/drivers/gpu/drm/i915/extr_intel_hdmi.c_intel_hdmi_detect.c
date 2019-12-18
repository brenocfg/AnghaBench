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
struct intel_hdmi {int has_hdmi_sink; int has_audio; int rgb_quant_range_selectable; scalar_t__ force_audio; int /*<<< orphan*/  ddc_bus; } ;
struct intel_encoder {int /*<<< orphan*/  type; } ;
struct intel_digital_port {struct intel_encoder base; } ;
struct edid {int input; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_connector {struct drm_device* dev; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int DRM_EDID_INPUT_DIGITAL ; 
 scalar_t__ HDMI_AUDIO_AUTO ; 
 scalar_t__ HDMI_AUDIO_OFF_DVI ; 
 scalar_t__ HDMI_AUDIO_ON ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int drm_detect_hdmi_monitor (struct edid*) ; 
 int drm_detect_monitor_audio (struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int drm_rgb_quant_range_selectable (struct edid*) ; 
 struct intel_digital_port* hdmi_to_dig_port (struct intel_hdmi*) ; 
 struct intel_hdmi* intel_attached_hdmi (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_gmbus_get_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static enum drm_connector_status
intel_hdmi_detect(struct drm_connector *connector, bool force)
{
	struct drm_device *dev = connector->dev;
	struct intel_hdmi *intel_hdmi = intel_attached_hdmi(connector);
	struct intel_digital_port *intel_dig_port =
		hdmi_to_dig_port(intel_hdmi);
	struct intel_encoder *intel_encoder = &intel_dig_port->base;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct edid *edid;
	enum drm_connector_status status = connector_status_disconnected;

	intel_hdmi->has_hdmi_sink = false;
	intel_hdmi->has_audio = false;
	intel_hdmi->rgb_quant_range_selectable = false;
	edid = drm_get_edid(connector,
			    intel_gmbus_get_adapter(dev_priv,
						    intel_hdmi->ddc_bus));

	if (edid) {
		if (edid->input & DRM_EDID_INPUT_DIGITAL) {
			status = connector_status_connected;
			if (intel_hdmi->force_audio != HDMI_AUDIO_OFF_DVI)
				intel_hdmi->has_hdmi_sink =
						drm_detect_hdmi_monitor(edid);
			intel_hdmi->has_audio = drm_detect_monitor_audio(edid);
			intel_hdmi->rgb_quant_range_selectable =
				drm_rgb_quant_range_selectable(edid);
		}
		kfree(edid);
	}

	if (status == connector_status_connected) {
		if (intel_hdmi->force_audio != HDMI_AUDIO_AUTO)
			intel_hdmi->has_audio =
				(intel_hdmi->force_audio == HDMI_AUDIO_ON);
		intel_encoder->type = INTEL_OUTPUT_HDMI;
	}

	return status;
}