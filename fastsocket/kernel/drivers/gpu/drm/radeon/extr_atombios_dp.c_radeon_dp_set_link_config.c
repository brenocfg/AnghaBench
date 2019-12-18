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
struct radeon_connector_atom_dig {scalar_t__ dp_sink_type; int /*<<< orphan*/  dpcd; int /*<<< orphan*/  dp_lane_count; int /*<<< orphan*/  dp_clock; } ;
struct radeon_connector {struct radeon_connector_atom_dig* con_priv; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 scalar_t__ CONNECTOR_OBJECT_ID_DISPLAYPORT ; 
 scalar_t__ CONNECTOR_OBJECT_ID_eDP ; 
 int /*<<< orphan*/  radeon_dp_get_dp_lane_number (struct drm_connector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_dp_get_dp_link_clock (struct drm_connector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

void radeon_dp_set_link_config(struct drm_connector *connector,
			       const struct drm_display_mode *mode)
{
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	struct radeon_connector_atom_dig *dig_connector;

	if (!radeon_connector->con_priv)
		return;
	dig_connector = radeon_connector->con_priv;

	if ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
	    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP)) {
		dig_connector->dp_clock =
			radeon_dp_get_dp_link_clock(connector, dig_connector->dpcd, mode->clock);
		dig_connector->dp_lane_count =
			radeon_dp_get_dp_lane_number(connector, dig_connector->dpcd, mode->clock);
	}
}