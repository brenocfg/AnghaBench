#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {scalar_t__ fitting_mode; } ;
struct intel_connector {TYPE_3__ panel; } ;
struct drm_property {int dummy; } ;
struct TYPE_6__ {struct drm_property* scaling_mode_property; } ;
struct drm_device {TYPE_2__ mode_config; } ;
struct drm_crtc {scalar_t__ enabled; } ;
struct drm_connector {struct drm_device* dev; } ;
struct TYPE_5__ {struct drm_crtc* crtc; } ;
struct TYPE_8__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ DRM_MODE_SCALE_NONE ; 
 int EINVAL ; 
 TYPE_4__* intel_attached_encoder (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_crtc_restore_mode (struct drm_crtc*) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static int intel_lvds_set_property(struct drm_connector *connector,
				   struct drm_property *property,
				   uint64_t value)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);
	struct drm_device *dev = connector->dev;

	if (property == dev->mode_config.scaling_mode_property) {
		struct drm_crtc *crtc;

		if (value == DRM_MODE_SCALE_NONE) {
			DRM_DEBUG_KMS("no scaling not supported\n");
			return -EINVAL;
		}

		if (intel_connector->panel.fitting_mode == value) {
			/* the LVDS scaling property is not changed */
			return 0;
		}
		intel_connector->panel.fitting_mode = value;

		crtc = intel_attached_encoder(connector)->base.crtc;
		if (crtc && crtc->enabled) {
			/*
			 * If the CRTC is enabled, the display will be changed
			 * according to the new panel fitting mode.
			 */
			intel_crtc_restore_mode(crtc);
		}
	}

	return 0;
}