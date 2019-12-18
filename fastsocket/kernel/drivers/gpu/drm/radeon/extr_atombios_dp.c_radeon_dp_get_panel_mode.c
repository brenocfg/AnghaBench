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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct radeon_device {int dummy; } ;
struct radeon_connector {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {scalar_t__ connector_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_DCE4 (struct radeon_device*) ; 
 int /*<<< orphan*/  DP_EDP_CONFIGURATION_CAP ; 
 int DP_PANEL_MODE_EXTERNAL_DP_MODE ; 
 int DP_PANEL_MODE_INTERNAL_DP1_MODE ; 
 int DP_PANEL_MODE_INTERNAL_DP2_MODE ; 
 scalar_t__ DRM_MODE_CONNECTOR_eDP ; 
 scalar_t__ ENCODER_OBJECT_ID_NONE ; 
 scalar_t__ ENCODER_OBJECT_ID_NUTMEG ; 
 scalar_t__ ENCODER_OBJECT_ID_TRAVIS ; 
 scalar_t__ radeon_connector_encoder_get_dp_bridge_encoder_id (struct drm_connector*) ; 
 int radeon_read_dpcd_reg (struct radeon_connector*,int /*<<< orphan*/ ) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

int radeon_dp_get_panel_mode(struct drm_encoder *encoder,
			     struct drm_connector *connector)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	int panel_mode = DP_PANEL_MODE_EXTERNAL_DP_MODE;
	u16 dp_bridge = radeon_connector_encoder_get_dp_bridge_encoder_id(connector);
	u8 tmp;

	if (!ASIC_IS_DCE4(rdev))
		return panel_mode;

	if (dp_bridge != ENCODER_OBJECT_ID_NONE) {
		/* DP bridge chips */
		tmp = radeon_read_dpcd_reg(radeon_connector, DP_EDP_CONFIGURATION_CAP);
		if (tmp & 1)
			panel_mode = DP_PANEL_MODE_INTERNAL_DP2_MODE;
		else if ((dp_bridge == ENCODER_OBJECT_ID_NUTMEG) ||
			 (dp_bridge == ENCODER_OBJECT_ID_TRAVIS))
			panel_mode = DP_PANEL_MODE_INTERNAL_DP1_MODE;
		else
			panel_mode = DP_PANEL_MODE_EXTERNAL_DP_MODE;
	} else if (connector->connector_type == DRM_MODE_CONNECTOR_eDP) {
		/* eDP */
		tmp = radeon_read_dpcd_reg(radeon_connector, DP_EDP_CONFIGURATION_CAP);
		if (tmp & 1)
			panel_mode = DP_PANEL_MODE_INTERNAL_DP2_MODE;
	}

	return panel_mode;
}