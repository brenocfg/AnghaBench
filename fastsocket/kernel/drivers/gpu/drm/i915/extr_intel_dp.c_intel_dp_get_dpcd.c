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
struct intel_dp {int* dpcd; int* downstream_ports; } ;
typedef  int /*<<< orphan*/  dpcd_hex_dump ;

/* Variables and functions */
 size_t DP_DOWNSTREAMPORT_PRESENT ; 
 int DP_DOWNSTREAM_PORT_0 ; 
 size_t DP_DPCD_REV ; 
 int DP_DWN_STRM_PORT_PRESENT ; 
 int DP_MAX_DOWNSTREAM_PORTS ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*) ; 
 int /*<<< orphan*/  hex_dump_to_buffer (int*,int,int,int,char*,int,int) ; 
 scalar_t__ intel_dp_aux_native_read_retry (struct intel_dp*,int,int*,int) ; 

__attribute__((used)) static bool
intel_dp_get_dpcd(struct intel_dp *intel_dp)
{
	char dpcd_hex_dump[sizeof(intel_dp->dpcd) * 3];

	if (intel_dp_aux_native_read_retry(intel_dp, 0x000, intel_dp->dpcd,
					   sizeof(intel_dp->dpcd)) == 0)
		return false; /* aux transfer failed */

	hex_dump_to_buffer(intel_dp->dpcd, sizeof(intel_dp->dpcd),
			   32, 1, dpcd_hex_dump, sizeof(dpcd_hex_dump), false);
	DRM_DEBUG_KMS("DPCD: %s\n", dpcd_hex_dump);

	if (intel_dp->dpcd[DP_DPCD_REV] == 0)
		return false; /* DPCD not present */

	if (!(intel_dp->dpcd[DP_DOWNSTREAMPORT_PRESENT] &
	      DP_DWN_STRM_PORT_PRESENT))
		return true; /* native DP sink */

	if (intel_dp->dpcd[DP_DPCD_REV] == 0x10)
		return true; /* no per-port downstream info */

	if (intel_dp_aux_native_read_retry(intel_dp, DP_DOWNSTREAM_PORT_0,
					   intel_dp->downstream_ports,
					   DP_MAX_DOWNSTREAM_PORTS) == 0)
		return false; /* downstream port status fetch failed */

	return true;
}