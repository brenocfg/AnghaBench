#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct dcbx_app_priority_feature {scalar_t__ default_pri; struct dcbx_app_priority_entry* app_pri_tbl; scalar_t__ enabled; } ;
struct dcbx_app_priority_entry {scalar_t__ appBitfield; scalar_t__ app_id; int /*<<< orphan*/  pri_bitmap; } ;
struct TYPE_3__ {scalar_t__* traffic_type_priority; int enabled; } ;
struct TYPE_4__ {TYPE_1__ app; } ;
struct bnx2x {TYPE_2__ dcbx_port_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_DCB ; 
 int DCBX_APP_SF_ETH_TYPE ; 
 int DCBX_APP_SF_PORT ; 
 int DCBX_LOCAL_APP_ERROR ; 
 int DCBX_LOCAL_APP_MISMATCH ; 
 size_t DCBX_MAX_APP_PROTOCOL ; 
 int DCBX_REMOTE_APP_TLV_NOT_FOUND ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ETH_TYPE_FCOE ; 
 scalar_t__ GET_FLAGS (scalar_t__,int) ; 
 scalar_t__ INVALID_TRAFFIC_TYPE_PRIORITY ; 
 size_t LLFC_DRIVER_TRAFFIC_TYPE_MAX ; 
 int /*<<< orphan*/  LLFC_TRAFFIC_TYPE_FCOE ; 
 int /*<<< orphan*/  LLFC_TRAFFIC_TYPE_ISCSI ; 
 size_t LLFC_TRAFFIC_TYPE_NW ; 
 scalar_t__ MAX_PFC_PRIORITIES ; 
 scalar_t__ TCP_PORT_ISCSI ; 
 int /*<<< orphan*/  bnx2x_dcbx_get_ap_priority (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_dcbx_get_ap_feature(struct bnx2x *bp,
				   struct dcbx_app_priority_feature *app,
				   u32 error) {
	u8 index;
	u32 *ttp = bp->dcbx_port_params.app.traffic_type_priority;

	if (GET_FLAGS(error, DCBX_LOCAL_APP_ERROR))
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_APP_ERROR\n");

	if (GET_FLAGS(error, DCBX_LOCAL_APP_MISMATCH))
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_APP_MISMATCH\n");

	if (GET_FLAGS(error, DCBX_REMOTE_APP_TLV_NOT_FOUND))
		DP(BNX2X_MSG_DCB, "DCBX_REMOTE_APP_TLV_NOT_FOUND\n");
	if (app->enabled &&
	    !GET_FLAGS(error, DCBX_LOCAL_APP_ERROR | DCBX_LOCAL_APP_MISMATCH |
			      DCBX_REMOTE_APP_TLV_NOT_FOUND)) {

		bp->dcbx_port_params.app.enabled = true;

		for (index = 0 ; index < LLFC_DRIVER_TRAFFIC_TYPE_MAX; index++)
			ttp[index] = 0;

		if (app->default_pri < MAX_PFC_PRIORITIES)
			ttp[LLFC_TRAFFIC_TYPE_NW] = app->default_pri;

		for (index = 0 ; index < DCBX_MAX_APP_PROTOCOL; index++) {
			struct dcbx_app_priority_entry *entry =
							app->app_pri_tbl;

			if (GET_FLAGS(entry[index].appBitfield,
				     DCBX_APP_SF_ETH_TYPE) &&
			   ETH_TYPE_FCOE == entry[index].app_id)
				bnx2x_dcbx_get_ap_priority(bp,
						entry[index].pri_bitmap,
						LLFC_TRAFFIC_TYPE_FCOE);

			if (GET_FLAGS(entry[index].appBitfield,
				     DCBX_APP_SF_PORT) &&
			   TCP_PORT_ISCSI == entry[index].app_id)
				bnx2x_dcbx_get_ap_priority(bp,
						entry[index].pri_bitmap,
						LLFC_TRAFFIC_TYPE_ISCSI);
		}
	} else {
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_APP_DISABLED\n");
		bp->dcbx_port_params.app.enabled = false;
		for (index = 0 ; index < LLFC_DRIVER_TRAFFIC_TYPE_MAX; index++)
			ttp[index] = INVALID_TRAFFIC_TYPE_PRIORITY;
	}
}