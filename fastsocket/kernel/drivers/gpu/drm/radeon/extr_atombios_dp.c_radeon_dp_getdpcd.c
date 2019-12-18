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
struct radeon_connector_atom_dig {scalar_t__* dpcd; } ;
struct radeon_connector {struct radeon_connector_atom_dig* con_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DPCD_REV ; 
 int DP_DPCD_SIZE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int radeon_dp_aux_native_read (struct radeon_connector*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_dp_probe_oui (struct radeon_connector*) ; 

bool radeon_dp_getdpcd(struct radeon_connector *radeon_connector)
{
	struct radeon_connector_atom_dig *dig_connector = radeon_connector->con_priv;
	u8 msg[DP_DPCD_SIZE];
	int ret, i;

	ret = radeon_dp_aux_native_read(radeon_connector, DP_DPCD_REV, msg,
					DP_DPCD_SIZE, 0);
	if (ret > 0) {
		memcpy(dig_connector->dpcd, msg, DP_DPCD_SIZE);
		DRM_DEBUG_KMS("DPCD: ");
		for (i = 0; i < DP_DPCD_SIZE; i++)
			DRM_DEBUG_KMS("%02x ", msg[i]);
		DRM_DEBUG_KMS("\n");

		radeon_dp_probe_oui(radeon_connector);

		return true;
	}
	dig_connector->dpcd[0] = 0;
	return false;
}