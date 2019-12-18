#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_dp {int color_range_auto; } ;
struct TYPE_5__ {int /*<<< orphan*/  fitting_mode; } ;
struct intel_connector {TYPE_2__ panel; } ;
struct drm_connector {TYPE_3__* dev; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  scaling_mode_property; } ;
struct TYPE_6__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_SCALE_ASPECT ; 
 int /*<<< orphan*/  drm_mode_create_scaling_mode_property (TYPE_3__*) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_attach_broadcast_rgb_property (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_attach_force_audio_property (struct drm_connector*) ; 
 scalar_t__ is_edp (struct intel_dp*) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static void
intel_dp_add_properties(struct intel_dp *intel_dp, struct drm_connector *connector)
{
	struct intel_connector *intel_connector = to_intel_connector(connector);

	intel_attach_force_audio_property(connector);
	intel_attach_broadcast_rgb_property(connector);
	intel_dp->color_range_auto = true;

	if (is_edp(intel_dp)) {
		drm_mode_create_scaling_mode_property(connector->dev);
		drm_object_attach_property(
			&connector->base,
			connector->dev->mode_config.scaling_mode_property,
			DRM_MODE_SCALE_ASPECT);
		intel_connector->panel.fitting_mode = DRM_MODE_SCALE_ASPECT;
	}
}