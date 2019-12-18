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
struct radeon_connector_atom_dig {int /*<<< orphan*/  edp_on; } ;
struct radeon_connector {struct radeon_connector_atom_dig* con_priv; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct drm_connector {scalar_t__ connector_type; TYPE_1__ display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_POWER_OFF ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_POWER_ON ; 
 scalar_t__ DRM_MODE_CONNECTOR_LVDS ; 
 scalar_t__ DRM_MODE_CONNECTOR_eDP ; 
 scalar_t__ ENCODER_OBJECT_ID_NONE ; 
 int /*<<< orphan*/  atombios_set_edp_panel_power (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  radeon_add_common_modes (struct drm_encoder*,struct drm_connector*) ; 
 int /*<<< orphan*/  radeon_atom_ext_encoder_setup_ddc (struct drm_encoder*) ; 
 struct drm_encoder* radeon_best_single_encoder (struct drm_connector*) ; 
 scalar_t__ radeon_connector_encoder_get_dp_bridge_encoder_id (struct drm_connector*) ; 
 int radeon_ddc_get_modes (struct radeon_connector*) ; 
 int /*<<< orphan*/  radeon_fixup_lvds_native_mode (struct drm_encoder*,struct drm_connector*) ; 
 struct drm_display_mode* radeon_fp_native_mode (struct drm_encoder*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

__attribute__((used)) static int radeon_dp_get_modes(struct drm_connector *connector)
{
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	struct radeon_connector_atom_dig *radeon_dig_connector = radeon_connector->con_priv;
	struct drm_encoder *encoder = radeon_best_single_encoder(connector);
	int ret;

	if ((connector->connector_type == DRM_MODE_CONNECTOR_eDP) ||
	    (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)) {
		struct drm_display_mode *mode;

		if (connector->connector_type == DRM_MODE_CONNECTOR_eDP) {
			if (!radeon_dig_connector->edp_on)
				atombios_set_edp_panel_power(connector,
							     ATOM_TRANSMITTER_ACTION_POWER_ON);
			ret = radeon_ddc_get_modes(radeon_connector);
			if (!radeon_dig_connector->edp_on)
				atombios_set_edp_panel_power(connector,
							     ATOM_TRANSMITTER_ACTION_POWER_OFF);
		} else {
			/* need to setup ddc on the bridge */
			if (radeon_connector_encoder_get_dp_bridge_encoder_id(connector) !=
			    ENCODER_OBJECT_ID_NONE) {
				if (encoder)
					radeon_atom_ext_encoder_setup_ddc(encoder);
			}
			ret = radeon_ddc_get_modes(radeon_connector);
		}

		if (ret > 0) {
			if (encoder) {
				radeon_fixup_lvds_native_mode(encoder, connector);
				/* add scaled modes */
				radeon_add_common_modes(encoder, connector);
			}
			return ret;
		}

		if (!encoder)
			return 0;

		/* we have no EDID modes */
		mode = radeon_fp_native_mode(encoder);
		if (mode) {
			ret = 1;
			drm_mode_probed_add(connector, mode);
			/* add the width/height from vbios tables if available */
			connector->display_info.width_mm = mode->width_mm;
			connector->display_info.height_mm = mode->height_mm;
			/* add scaled modes */
			radeon_add_common_modes(encoder, connector);
		}
	} else {
		/* need to setup ddc on the bridge */
		if (radeon_connector_encoder_get_dp_bridge_encoder_id(connector) !=
			ENCODER_OBJECT_ID_NONE) {
			if (encoder)
				radeon_atom_ext_encoder_setup_ddc(encoder);
		}
		ret = radeon_ddc_get_modes(radeon_connector);
	}

	return ret;
}