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
struct intel_dp {int dummy; } ;
struct intel_digital_port {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int connector_status_unknown ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  ibx_digital_port_connected (struct drm_i915_private*,struct intel_digital_port*) ; 
 int intel_dp_detect_dpcd (struct intel_dp*) ; 
 struct drm_device* intel_dp_to_dev (struct intel_dp*) ; 
 int intel_panel_detect (struct drm_device*) ; 
 scalar_t__ is_edp (struct intel_dp*) ; 

__attribute__((used)) static enum drm_connector_status
ironlake_dp_detect(struct intel_dp *intel_dp)
{
	struct drm_device *dev = intel_dp_to_dev(intel_dp);
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	enum drm_connector_status status;

	/* Can't disconnect eDP, but you can close the lid... */
	if (is_edp(intel_dp)) {
		status = intel_panel_detect(dev);
		if (status == connector_status_unknown)
			status = connector_status_connected;
		return status;
	}

	if (!ibx_digital_port_connected(dev_priv, intel_dig_port))
		return connector_status_disconnected;

	return intel_dp_detect_dpcd(intel_dp);
}