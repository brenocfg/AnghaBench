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
struct TYPE_2__ {scalar_t__ crtc; } ;
struct intel_encoder {int connectors_active; TYPE_1__ base; } ;
struct drm_connector {int dpms; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_MODE_DPMS_OFF ; 
 int DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct intel_encoder* intel_attached_encoder (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_encoder_dpms (struct intel_encoder*,int) ; 
 int /*<<< orphan*/  intel_modeset_check_state (int /*<<< orphan*/ ) ; 

void intel_connector_dpms(struct drm_connector *connector, int mode)
{
	struct intel_encoder *encoder = intel_attached_encoder(connector);

	/* All the simple cases only support two dpms states. */
	if (mode != DRM_MODE_DPMS_ON)
		mode = DRM_MODE_DPMS_OFF;

	if (mode == connector->dpms)
		return;

	connector->dpms = mode;

	/* Only need to change hw state when actually enabled */
	if (encoder->base.crtc)
		intel_encoder_dpms(encoder, mode);
	else
		WARN_ON(encoder->connectors_active != false);

	intel_modeset_check_state(connector->dev);
}