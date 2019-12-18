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
typedef  int /*<<< orphan*/  u8 ;
struct radeon_connector_atom_dig {int* dpcd; } ;
struct radeon_connector {struct radeon_connector_atom_dig* con_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_BRANCH_OUI ; 
 size_t DP_DOWN_STREAM_PORT_COUNT ; 
 int DP_OUI_SUPPORT ; 
 int /*<<< orphan*/  DP_SINK_OUI ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ radeon_dp_aux_native_read (struct radeon_connector*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_dp_probe_oui(struct radeon_connector *radeon_connector)
{
	struct radeon_connector_atom_dig *dig_connector = radeon_connector->con_priv;
	u8 buf[3];

	if (!(dig_connector->dpcd[DP_DOWN_STREAM_PORT_COUNT] & DP_OUI_SUPPORT))
		return;

	if (radeon_dp_aux_native_read(radeon_connector, DP_SINK_OUI, buf, 3, 0))
		DRM_DEBUG_KMS("Sink OUI: %02hx%02hx%02hx\n",
			      buf[0], buf[1], buf[2]);

	if (radeon_dp_aux_native_read(radeon_connector, DP_BRANCH_OUI, buf, 3, 0))
		DRM_DEBUG_KMS("Branch OUI: %02hx%02hx%02hx\n",
			      buf[0], buf[1], buf[2]);
}