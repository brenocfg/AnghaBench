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
struct intel_encoder {scalar_t__ type; } ;
struct intel_dp {int has_audio; scalar_t__ force_audio; int /*<<< orphan*/  adapter; } ;
struct intel_digital_port {struct intel_encoder base; } ;
struct edid {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 scalar_t__ HDMI_AUDIO_AUTO ; 
 scalar_t__ HDMI_AUDIO_ON ; 
 scalar_t__ INTEL_OUTPUT_DISPLAYPORT ; 
 scalar_t__ INTEL_OUTPUT_EDP ; 
 int connector_status_connected ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int drm_detect_monitor_audio (struct edid*) ; 
 int g4x_dp_detect (struct intel_dp*) ; 
 struct intel_dp* intel_attached_dp (struct drm_connector*) ; 
 struct edid* intel_dp_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_dp_probe_oui (struct intel_dp*) ; 
 int ironlake_dp_detect (struct intel_dp*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static enum drm_connector_status
intel_dp_detect(struct drm_connector *connector, bool force)
{
	struct intel_dp *intel_dp = intel_attached_dp(connector);
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct intel_encoder *intel_encoder = &intel_dig_port->base;
	struct drm_device *dev = connector->dev;
	enum drm_connector_status status;
	struct edid *edid = NULL;

	intel_dp->has_audio = false;

	if (HAS_PCH_SPLIT(dev))
		status = ironlake_dp_detect(intel_dp);
	else
		status = g4x_dp_detect(intel_dp);

	if (status != connector_status_connected)
		return status;

	intel_dp_probe_oui(intel_dp);

	if (intel_dp->force_audio != HDMI_AUDIO_AUTO) {
		intel_dp->has_audio = (intel_dp->force_audio == HDMI_AUDIO_ON);
	} else {
		edid = intel_dp_get_edid(connector, &intel_dp->adapter);
		if (edid) {
			intel_dp->has_audio = drm_detect_monitor_audio(edid);
			kfree(edid);
		}
	}

	if (intel_encoder->type != INTEL_OUTPUT_EDP)
		intel_encoder->type = INTEL_OUTPUT_DISPLAYPORT;
	return connector_status_connected;
}