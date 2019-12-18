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
struct drm_display_mode {int hdisplay; int vdisplay; } ;
struct radeon_encoder {struct drm_display_mode native_mode; } ;
struct radeon_device {int dummy; } ;
struct radeon_connector_atom_dig {scalar_t__ dp_sink_type; int /*<<< orphan*/  edp_on; } ;
struct TYPE_2__ {int /*<<< orphan*/  hpd; } ;
struct radeon_connector {TYPE_1__ hpd; scalar_t__ dac_load_detect; int /*<<< orphan*/ * edid; struct radeon_connector_atom_dig* con_priv; } ;
struct drm_encoder_helper_funcs {int (* detect ) (struct drm_encoder*,struct drm_connector*) ;} ;
struct drm_encoder {struct drm_encoder_helper_funcs* helper_private; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {int status; scalar_t__ connector_type; struct drm_device* dev; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_POWER_OFF ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_POWER_ON ; 
 scalar_t__ CONNECTOR_OBJECT_ID_DISPLAYPORT ; 
 scalar_t__ DRM_MODE_CONNECTOR_LVDS ; 
 scalar_t__ DRM_MODE_CONNECTOR_eDP ; 
 scalar_t__ ENCODER_OBJECT_ID_NONE ; 
 int /*<<< orphan*/  atombios_set_edp_panel_power (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_atom_ext_encoder_setup_ddc (struct drm_encoder*) ; 
 struct drm_encoder* radeon_best_single_encoder (struct drm_connector*) ; 
 scalar_t__ radeon_check_hpd_status_unchanged (struct drm_connector*) ; 
 scalar_t__ radeon_connector_encoder_get_dp_bridge_encoder_id (struct drm_connector*) ; 
 int /*<<< orphan*/  radeon_connector_update_scratch_regs (struct drm_connector*,int) ; 
 scalar_t__ radeon_ddc_probe (struct radeon_connector*,int) ; 
 scalar_t__ radeon_dp_getdpcd (struct radeon_connector*) ; 
 scalar_t__ radeon_dp_getsinktype (struct radeon_connector*) ; 
 scalar_t__ radeon_hpd_sense (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct drm_encoder*,struct drm_connector*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static enum drm_connector_status
radeon_dp_detect(struct drm_connector *connector, bool force)
{
	struct drm_device *dev = connector->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	enum drm_connector_status ret = connector_status_disconnected;
	struct radeon_connector_atom_dig *radeon_dig_connector = radeon_connector->con_priv;
	struct drm_encoder *encoder = radeon_best_single_encoder(connector);

	if (!force && radeon_check_hpd_status_unchanged(connector))
		return connector->status;

	if (radeon_connector->edid) {
		kfree(radeon_connector->edid);
		radeon_connector->edid = NULL;
	}

	if ((connector->connector_type == DRM_MODE_CONNECTOR_eDP) ||
	    (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)) {
		if (encoder) {
			struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
			struct drm_display_mode *native_mode = &radeon_encoder->native_mode;

			/* check if panel is valid */
			if (native_mode->hdisplay >= 320 && native_mode->vdisplay >= 240)
				ret = connector_status_connected;
		}
		/* eDP is always DP */
		radeon_dig_connector->dp_sink_type = CONNECTOR_OBJECT_ID_DISPLAYPORT;
		if (!radeon_dig_connector->edp_on)
			atombios_set_edp_panel_power(connector,
						     ATOM_TRANSMITTER_ACTION_POWER_ON);
		if (radeon_dp_getdpcd(radeon_connector))
			ret = connector_status_connected;
		if (!radeon_dig_connector->edp_on)
			atombios_set_edp_panel_power(connector,
						     ATOM_TRANSMITTER_ACTION_POWER_OFF);
	} else if (radeon_connector_encoder_get_dp_bridge_encoder_id(connector) !=
		   ENCODER_OBJECT_ID_NONE) {
		/* DP bridges are always DP */
		radeon_dig_connector->dp_sink_type = CONNECTOR_OBJECT_ID_DISPLAYPORT;
		/* get the DPCD from the bridge */
		radeon_dp_getdpcd(radeon_connector);

		if (encoder) {
			/* setup ddc on the bridge */
			radeon_atom_ext_encoder_setup_ddc(encoder);
			/* bridge chips are always aux */
			if (radeon_ddc_probe(radeon_connector, true)) /* try DDC */
				ret = connector_status_connected;
			else if (radeon_connector->dac_load_detect) { /* try load detection */
				struct drm_encoder_helper_funcs *encoder_funcs = encoder->helper_private;
				ret = encoder_funcs->detect(encoder, connector);
			}
		}
	} else {
		radeon_dig_connector->dp_sink_type = radeon_dp_getsinktype(radeon_connector);
		if (radeon_hpd_sense(rdev, radeon_connector->hpd.hpd)) {
			ret = connector_status_connected;
			if (radeon_dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT)
				radeon_dp_getdpcd(radeon_connector);
		} else {
			if (radeon_dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) {
				if (radeon_dp_getdpcd(radeon_connector))
					ret = connector_status_connected;
			} else {
				/* try non-aux ddc (DP to DVI/HMDI/etc. adapter) */
				if (radeon_ddc_probe(radeon_connector, false))
					ret = connector_status_connected;
			}
		}
	}

	radeon_connector_update_scratch_regs(connector, ret);
	return ret;
}