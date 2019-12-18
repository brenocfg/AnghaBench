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
struct radeon_encoder_atom_dig {size_t dig_encoder; int /*<<< orphan*/  afmt; } ;
struct radeon_encoder {int active_device; struct radeon_encoder_atom_dig* enc_priv; } ;
struct TYPE_5__ {int /*<<< orphan*/ * afmt; } ;
struct radeon_device {scalar_t__ family; TYPE_2__ mode_info; } ;
struct TYPE_6__ {scalar_t__ cd_valid; } ;
struct radeon_connector {TYPE_3__ router; } ;
struct drm_encoder {TYPE_1__* dev; } ;
struct drm_connector {scalar_t__ connector_type; } ;
struct TYPE_4__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int ATOM_DEVICE_DFP_SUPPORT ; 
 int ATOM_DEVICE_LCD_SUPPORT ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_ACTION_POWER_ON ; 
 scalar_t__ CHIP_R600 ; 
 scalar_t__ DRM_MODE_CONNECTOR_eDP ; 
 scalar_t__ ENCODER_OBJECT_ID_NONE ; 
 int /*<<< orphan*/  atombios_set_edp_panel_power (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_set_encoder_crtc_source (struct drm_encoder*) ; 
 int /*<<< orphan*/  radeon_atom_output_lock (struct drm_encoder*,int) ; 
 size_t radeon_atom_pick_dig_encoder (struct drm_encoder*) ; 
 scalar_t__ radeon_encoder_get_dp_bridge_encoder_id (struct drm_encoder*) ; 
 struct drm_connector* radeon_get_connector_for_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  radeon_router_select_cd_port (struct radeon_connector*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void radeon_atom_encoder_prepare(struct drm_encoder *encoder)
{
	struct radeon_device *rdev = encoder->dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct drm_connector *connector = radeon_get_connector_for_encoder(encoder);

	if ((radeon_encoder->active_device &
	     (ATOM_DEVICE_DFP_SUPPORT | ATOM_DEVICE_LCD_SUPPORT)) ||
	    (radeon_encoder_get_dp_bridge_encoder_id(encoder) !=
	     ENCODER_OBJECT_ID_NONE)) {
		struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
		if (dig) {
			dig->dig_encoder = radeon_atom_pick_dig_encoder(encoder);
			if (radeon_encoder->active_device & ATOM_DEVICE_DFP_SUPPORT) {
				if (rdev->family >= CHIP_R600)
					dig->afmt = rdev->mode_info.afmt[dig->dig_encoder];
				else
					/* RS600/690/740 have only 1 afmt block */
					dig->afmt = rdev->mode_info.afmt[0];
			}
		}
	}

	radeon_atom_output_lock(encoder, true);

	if (connector) {
		struct radeon_connector *radeon_connector = to_radeon_connector(connector);

		/* select the clock/data port if it uses a router */
		if (radeon_connector->router.cd_valid)
			radeon_router_select_cd_port(radeon_connector);

		/* turn eDP panel on for mode set */
		if (connector->connector_type == DRM_MODE_CONNECTOR_eDP)
			atombios_set_edp_panel_power(connector,
						     ATOM_TRANSMITTER_ACTION_POWER_ON);
	}

	/* this is needed for the pll/ss setup to work correctly in some cases */
	atombios_set_encoder_crtc_source(encoder);
}