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
struct TYPE_3__ {int /*<<< orphan*/  enabled; } ;
struct TYPE_4__ {TYPE_1__ ets; } ;
struct bnx2x {int dcbx_error; TYPE_2__ dcbx_port_params; int /*<<< orphan*/  link_vars; int /*<<< orphan*/  link_params; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E3B0 (struct bnx2x*) ; 
 int DCBX_REMOTE_MIB_ERROR ; 
 int DRV_FLAGS_DCB_MFW_CONFIGURED ; 
 scalar_t__ GET_FLAGS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SHMEM2_HAS (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM2_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_dcbx_2cos_limit_update_ets_config (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_dcbx_update_ets_config (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_ets_disabled (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv_flags ; 

__attribute__((used)) static void bnx2x_dcbx_update_ets_params(struct bnx2x *bp)
{
	int mfw_configured = SHMEM2_HAS(bp, drv_flags) &&
			     GET_FLAGS(SHMEM2_RD(bp, drv_flags),
				       1 << DRV_FLAGS_DCB_MFW_CONFIGURED);

	bnx2x_ets_disabled(&bp->link_params, &bp->link_vars);

	if (!bp->dcbx_port_params.ets.enabled ||
	    ((bp->dcbx_error & DCBX_REMOTE_MIB_ERROR) && !mfw_configured))
		return;

	if (CHIP_IS_E3B0(bp))
		bnx2x_dcbx_update_ets_config(bp);
	else
		bnx2x_dcbx_2cos_limit_update_ets_config(bp);
}