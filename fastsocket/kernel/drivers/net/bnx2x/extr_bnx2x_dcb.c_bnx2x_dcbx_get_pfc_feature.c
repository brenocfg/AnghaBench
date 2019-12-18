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
typedef  int /*<<< orphan*/  u32 ;
struct dcbx_pfc_feature {int /*<<< orphan*/  pri_en_bitmap; scalar_t__ enabled; } ;
struct TYPE_5__ {int enabled; int /*<<< orphan*/  priority_non_pauseable_mask; } ;
struct TYPE_4__ {scalar_t__ enabled; } ;
struct TYPE_6__ {TYPE_2__ pfc; TYPE_1__ app; } ;
struct bnx2x {TYPE_3__ dcbx_port_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_DCB ; 
 int DCBX_LOCAL_PFC_ERROR ; 
 int DCBX_LOCAL_PFC_MISMATCH ; 
 int DCBX_REMOTE_PFC_TLV_NOT_FOUND ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ GET_FLAGS (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void  bnx2x_dcbx_get_pfc_feature(struct bnx2x *bp,
					struct dcbx_pfc_feature *pfc, u32 error)
{
	if (GET_FLAGS(error, DCBX_LOCAL_PFC_ERROR))
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_PFC_ERROR\n");

	if (GET_FLAGS(error, DCBX_REMOTE_PFC_TLV_NOT_FOUND))
		DP(BNX2X_MSG_DCB, "DCBX_REMOTE_PFC_TLV_NOT_FOUND\n");
	if (bp->dcbx_port_params.app.enabled && pfc->enabled &&
	   !GET_FLAGS(error, DCBX_LOCAL_PFC_ERROR | DCBX_LOCAL_PFC_MISMATCH |
			     DCBX_REMOTE_PFC_TLV_NOT_FOUND)) {
		bp->dcbx_port_params.pfc.enabled = true;
		bp->dcbx_port_params.pfc.priority_non_pauseable_mask =
			~(pfc->pri_en_bitmap);
	} else {
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_PFC_DISABLED\n");
		bp->dcbx_port_params.pfc.enabled = false;
		bp->dcbx_port_params.pfc.priority_non_pauseable_mask = 0;
	}
}